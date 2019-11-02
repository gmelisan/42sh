/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_compound_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:57:35 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/11/02 16:35:55 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		traverse_compound_list(t_compound_list *list)
{
	char	*str;
	t_pjobs *local;

	if (g_is_interrupt)
		return ;
	str = get_job_name(list->lex_begin, list->lex_end);
	local = jobs_started(ft_xstrdup(str), 0);
	call_subshell(str, &local);
}
