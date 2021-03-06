/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 19:22:32 by jterry            #+#    #+#             */
/*   Updated: 2019/10/25 19:34:08 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_pjobs		*jobs_find_num(t_pjobs *local, int num)
{
	int		high;

	if (num == 0)
		high = find_highnum(local);
	else
		high = num;
	while (local && local->num != high)
		local = local->next;
	return (local);
}

t_job		*process_finder(int pid, t_pjobs *first_job)
{
	t_job *job;

	if (first_job)
	{
		job = first_job->job;
		while (job)
		{
			if (job->pid == pid)
				return (job);
			job = job->next;
		}
	}
	return (NULL);
}

t_pjobs		*job_finder(int pid, t_pjobs *local)
{
	t_job *job;

	while (local)
	{
		job = local->job;
		while (job)
		{
			if (job->pid == pid)
				return (local);
			job = job->next;
		}
		local = local->next;
	}
	return (NULL);
}
