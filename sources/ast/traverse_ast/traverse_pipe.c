/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:26:20 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/15 18:17:27 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "sem.h"

static void		handle_last_cmd_in_pipe(int fd, t_command *cmd, t_pjobs *local)
{
	pid_t		pid;

	if ((pid = fork()) == 0)
	{
		setpgid(getpid(), local->workgpid);
		if (local->flag == 0)
			tcsetpgrp(0, local->workgpid);
		reserve_sem(SEMPIPE, 1);
		dup2(fd, 0);
		close(fd);
		traverse_command(cmd, 1, local);
		exit(g_res_exec);
	}
	if (local->flag == 1)
		ft_printf(" %d\n", pid);
	local = ljobs_startet(get_process_name(cmd), local->flag, local->num, pid);
}

void			traverse_pipe(t_pipe_sequence *pipe_seq, int fd,
								t_pjobs *local, int *counter)
{
	pid_t		pid;
	int			pipefd[2];

	*counter += 1;
	if (pipe(pipefd) == -1)
		exit(-1);
	pid = fork();
	if (local->workgpid == 0)
		local->workgpid = pid;
	if (pid == 0)
	{
		setpgid(getpid(), local->workgpid);
		if (local->flag == 0)
			tcsetpgrp(0, local->workgpid);
		reserve_sem(SEMPIPE, 1);
		close(pipefd[0]);
		dup2(fd, 0);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		traverse_command(pipe_seq->command, 1, local);
		exit(g_res_exec);
	}
	close(pipefd[1]);
	if (local && local->flag == 1)
		ft_printf(" %d", pid);
	local = ljobs_startet(get_process_name(pipe_seq->command), local->flag, local->num, pid);
	pipe_seq = pipe_seq->next;
	if (pipe_seq->next)
		traverse_pipe(pipe_seq, pipefd[0], local, counter);
	else
		handle_last_cmd_in_pipe(pipefd[0], pipe_seq->command, local);
	close(pipefd[0]);
}
