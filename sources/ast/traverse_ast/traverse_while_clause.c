/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_while_clause.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:15:50 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/20 15:06:53 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	traverse_while_clause(t_while_clause *list, char **env, t_pjobs *local)
{
	if (list->compound_list)
	while (42)
	{
		traverse_compound_list(list->compound_list, env, local);
		if (g_res_exec)
			break ;
		traverse_compound_list(list->do_group, env, local);
	}
}
