/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:23:21 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/11/02 19:54:03 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern t_opt		g_opt;

static void			traverse_and_or(t_and_or *elem, int sep, int init_flag)
{
	static int		flag;

	flag = init_flag;
	if (elem->next)
		traverse_and_or(elem->next, sep, flag);
	if (g_opt.arithmetic_error)
		return ;
	if (!flag || (flag == AND_IF && !g_res_exec)
				|| (flag == OR_IF && g_res_exec))
	{
		traverse_pipe_sequence(elem->pipeline->pipe_sequence, sep);
		if (elem->pipeline->bang)
			g_res_exec = (!g_res_exec) ? 1 : 0;
	}
	flag = elem->and_or_if;
}

static int			cmd_is_subshell(t_and_or *and_or, int sep)
{
	if (sep == JOB)
	{
		if ((and_or->next) || (and_or->pipeline->pipe_sequence->command &&
				and_or->pipeline->pipe_sequence->command->compound_command))
			return (1);
	}
	return (0);
}

static void			traverse_list(t_pars_list *list, int sep)
{
	extern char		**environ;
	t_pjobs			*local;
	char			*pjobs_name;
	char			*sub_job_name;

	if (list->sep != JOB && list->next)
		traverse_list(list->next, list->next->sep);
	if (g_opt.arithmetic_error)
		return ;
	if (cmd_is_subshell(list->and_or, list->sep))
	{
		pjobs_name = get_job_name(list->lex_begin, list->lex_end);
		local = jobs_started(pjobs_name, sep);
		sub_job_name = get_job_name(list->lex_begin, list->lex_end);
		call_subshell(sub_job_name, &local);
	}
	else
		traverse_and_or(list->and_or, sep, 0);
}

void				traverse_ast(t_complete_cmd *root)
{
	if (!root)
		return ;
	signal_monitor();
	g_opt.arithmetic_error = 0;
	root->list->sep = root->sep;
	if (g_opt.is_subshell)
	{
		if (root->list->next || root->list->and_or->next)
			g_opt.is_single_cmd = 0;
	}
	traverse_list(root->list, root->sep);
	if (g_cur_job)
		deletejob(&g_cur_job, g_cur_job->num);
}
