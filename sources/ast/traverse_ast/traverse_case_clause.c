/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_case_clause.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:07:01 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/29 21:24:36 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	traverse_case_clause(t_case_clause *list, t_pjobs *local)
{
	printf("%s\n", list->word);
	(void)local;
	// while (list->case_list)
	// if (list->word)
	// 	while (42)
	// 	{
	// 		traverse_compound_list(list->case_list->case_item->compound_list, local);
	// 		if (g_res_exec)
	// 			break ;
	// 		traverse_compound_list(list->word, local);
	// 	}
}
