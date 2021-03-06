/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:46:45 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/11/02 01:27:02 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern char			**g_var;

static void			pipe_seq_simple_builtin(t_command *cmd, t_pjobs **local)
{
	pid_t			pid;

	if ((*local)->flag == 0 || ft_strequ("fc", cmd->simple_command->cmd_name))
		traverse_command(cmd, 0, local);
	else if ((*local)->flag == 1)
	{
		if ((pid = fork()) == 0)
		{
			setpgid(getpid(), getpid());
			traverse_command(cmd, 0, local);
			exit(g_res_exec);
		}
		else if (pid == -1)
			print_error_exit("fork error", NULL, 1);
		setpgid(pid, pid);
		(*local) = ljobs_started(get_process_name(cmd),
				(*local)->flag, (*local)->num, pid);
		ft_printf("[%d] [%d]\n", (*local)->num, pid);
	}
}

static void			pipe_seq_simple_non_builtin(t_command *cmd, t_pjobs **local,
																char *cmd_name)
{
	extern t_opt	g_opt;
	pid_t			pid;

	hash_add_count(cmd_name);
	if (g_opt.is_subshell && g_opt.is_single_cmd)
		return (traverse_command(cmd, 1, local));
	if ((pid = fork()) == 0)
	{
		setpgid(getpid(), getpid());
		if ((*local)->flag == 0)
			tcsetpgrp(0, getpid());
		traverse_command(cmd, 1, local);
	}
	else if (pid == -1)
		print_error_exit("fork error", NULL, 1);
	setpgid(pid, pid);
	(*local) = ljobs_started(get_process_name(cmd),
					(*local)->flag, (*local)->num, pid);
	if ((*local)->flag == 1)
		ft_printf("[%d] [%d]\n", (*local)->num, pid);
	else
	{
		tcsetpgrp(0, pid);
		ft_waitpid(pid, NULL);
	}
}

static void			pipe_seq_without_pipe(t_command *cmd, t_pjobs **local)
{
	char			*cmd_name;

	if (cmd->simple_command)
	{
		cmd->simple_command->cmd_name = tdq(cmd->simple_command->cmd_name,
																	local);
		if ((cmd_name = cmd->simple_command->cmd_name))
		{
			if (is_builtin(cmd_name))
				pipe_seq_simple_builtin(cmd, local);
			else if (check_cmd(cmd_name) == 0)
				pipe_seq_simple_non_builtin(cmd, local, cmd_name);
			else if ((*local)->job)
				freedsubjob(&(*local)->job);
		}
		else
			traverse_command(cmd, 0, local);
	}
	else
		traverse_command(cmd, 0, local);
	if (cmd->simple_command)
		redir_reset();
}

extern int			g_open;

void				traverse_pipe_sequence(t_pipe_sequence *pipe_seq, int sep)
{
	t_pjobs			*local;
	char			*pjobs_name;
	int				counter;

	pjobs_name = get_job_name(pipe_seq->lex_begin, pipe_seq->lex_end);
	local = jobs_started(pjobs_name, sep);
	counter = 1;
	if (pipe_seq->next)
	{
		if (local->flag == 1)
			ft_printf("[%d]", local->num);
		traverse_pipe(pipe_seq, 0, &local, &counter);
		if (local->flag == 0)
			tcsetpgrp(0, local->workgpid);
		pipe_av(counter);
		if (local->flag == 0)
			ft_waitpid(-1, local->job);
	}
	else
		pipe_seq_without_pipe(pipe_seq->command, &local);
}
