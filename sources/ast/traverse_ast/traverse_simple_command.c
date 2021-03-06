/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:34:50 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/30 19:37:50 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern char		**g_var;
extern t_opt	g_opt;

static int		traverse_cmd_pref(t_cmd_prefix *pref, t_vector *prefix_vars,
															t_pjobs **local)
{
	while (pref)
	{
		if (pref->assignment_word)
		{
			pref->assignment_word = tdq(pref->assignment_word, local);
			vec_addback(prefix_vars, &(pref->assignment_word));
		}
		else if (redirect(pref->io_redir, local) == -1)
		{
			g_res_exec = 1;
			redir_reset();
			return (-1);
		}
		pref = pref->cmd_pref;
	}
	return (0);
}

static int		traverse_cmd_suf(t_cmd_suffix *suff, t_vector *av,
														t_pjobs **local)
{
	while (suff)
	{
		if (suff->word)
		{
			suff->word = tdq(suff->word, local);
			vec_addback(av, &(suff->word));
		}
		else if (redirect(suff->io_redir, local) == -1)
		{
			g_res_exec = 1;
			redir_reset();
			return (-1);
		}
		suff = suff->cmd_suf;
	}
	return (0);
}

static void		handle_previx_vars(const char **av, char ***env)
{
	while (*av)
		set_var(*(av++), env, 0);
}

static void		traverse_cmd_error(int in_fork, t_vector av,
												t_vector prefix_vars)
{
	ft_memdel(&av.v);
	ft_memdel(&prefix_vars.v);
	g_prefix_vars = NULL;
	redir_reset();
	if (in_fork)
		exit(g_res_exec);
}

void			traverse_simple_command(t_simple_cmd *cmd, int in_fork,
														t_pjobs **local)
{
	t_vector	av;
	t_vector	prefix_vars;
	extern char	**environ;

	redir_set();
	av = vec_create(0, sizeof(char *));
	if (cmd->cmd_name)
		vec_addback(&av, &(cmd->cmd_name));
	prefix_vars = vec_create(0, sizeof(char *));
	if (traverse_cmd_pref(cmd->cmd_pref, &prefix_vars, local) == -1
			|| traverse_cmd_suf(cmd->cmd_suf, &av, local) == -1
			|| g_opt.arithmetic_error)
		return (traverse_cmd_error(in_fork, av, prefix_vars));
	if (in_fork && prefix_vars.len)
		handle_previx_vars((const char **)prefix_vars.v, &environ);
	else if (prefix_vars.len)
		g_prefix_vars = (char **)prefix_vars.v;
	if (av.len)
		call_exec((int)av.len, (const char **)av.v, local);
	else if (prefix_vars.len)
		handle_previx_vars((const char **)prefix_vars.v, &g_var);
	traverse_cmd_error(in_fork, av, prefix_vars);
}
