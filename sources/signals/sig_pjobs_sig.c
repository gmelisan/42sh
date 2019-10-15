/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_pjobs_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:28:50 by jterry            #+#    #+#             */
/*   Updated: 2019/10/15 19:05:31 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		def_kill_or_done(t_job *first, int sig, char *name)
{
	char *msg;

	if ((msg = that_sig(sig, g_pjobs->name)))
	{
		ft_printf("[%d]\t%s\n", first->num, msg);
		free(msg);
	}
	else if (sig != 2 && sig != 256)
	{
		if (sig == 0)
			ft_printf("[%d]\tDone  \t\t%s\n", first->num, name);
		else
			ft_printf("[%d]\tExit %d\t\t%s\n", first->num, sig, name);
	}
	if (!(first->next))
		deletejob(&g_pjobs, first->num);
	else
	{
		free(first->status);
		first->status = ft_xstrdup("Done\t\t");
	}
}

void			pjobs_sig(int sig, int done_pid)
{
	t_pjobs			*first;
	t_job			*job;

	job = NULL;
	job = job_finder(done_pid, g_pjobs);
	if (job == NULL)
		return ;
	first = jobs_find_num(g_pjobs, job->num);
	if (done_pid != 0 && sig != SUSPINT && sig != SUSPOUT && !(job->next))
		def_kill_or_done(job, sig, first->name);
	else if (sig == SUSPINT || sig == SUSPOUT)
	{
		free(first->status);
		if (sig == SUSPINT)
			first->status = ft_xstrdup(" suspended (tty input)\t");
		if (sig == SUSPOUT)
			first->status = ft_xstrdup(" suspended (tty output)\t");
		free(job->status);
		job->status = ft_xstrdup("suspended");
	}
}
