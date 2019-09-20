/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:23:21 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/20 15:57:23 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			pid_fredy()
{
	int i;

	i = -1;
	if (g_pipe_pid)
	{
		while (g_pipe_pid[++i] != 0)
			g_pipe_pid[i] = 0;
		free(g_pipe_pid);
		g_pipe_pid = NULL;
	}
	g_wait_flags = 0;
	return (1);
}

static void		traverse_and_or(t_and_or *elem, int flag1, t_pjobs *local)
{
	extern char	**environ;
	static int	flag;

	flag = flag1;
	if (elem->next)
		traverse_and_or(elem->next, flag, local);
	if (!flag || (flag == AND_IF && !g_res_exec)
				|| (flag == OR_IF && g_res_exec))
	{
		traverse_pipe_sequence(elem->pipeline->pipe_sequence, environ, local);
		pid_fredy();
		if (elem->pipeline->bang)
		{
			g_res_exec = (!g_res_exec) ? 1 : 0;
			set_result();
		}
	}
	else
		return ;
	flag = elem->and_or_if;
}

static void		traverse_list(t_pars_list *list, int sep)
{
	t_pjobs		*local;
	char		*pjobs_name;
	extern char	**environ;

	if (list->next)
		traverse_list(list->next, list->next->sep);
	g_res_exec = 0;
	pjobs_name = get_job_name(list->lex_begin, list->lex_end, 0);
	local = jobs_startet(pjobs_name, sep);
	if (list->and_or->next)
		local->workgpid = 1;
	if (list->sep == JOB)
	{
		pjobs_name = get_job_name(list->lex_begin, list->lex_end, list->sep);
		call_subshell(pjobs_name, list->sep, environ, local);
		free(pjobs_name);
	}
	else
		traverse_and_or(list->and_or, 0, local);
}

void			traverse_ast(t_complete_cmd *root)
{
	if (!root)
		return ;
	root->list->sep = root->sep;
	traverse_list(root->list, root->sep);
}
