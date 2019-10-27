/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_until_clause.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:42:34 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/27 16:57:01 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
** until_clause	: Until compound_list Do compound_list Done
*/

void	traverse_until_clause(t_while_clause *list, t_pjobs **local)
{
	if (list->compound_list)
		while (1 && !g_is_interrupt)
		{
			traverse_compound_list(list->compound_list, local);
			if (!g_res_exec || g_is_interrupt)
				break ;
			traverse_compound_list(list->do_group, local);
		}
}
