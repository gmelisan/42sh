/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hash_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 17:49:40 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/06 15:38:32 by wtalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		fill_hash_table(void)
{
	extern	t_hash	**g_table;

	if (g_table)
		del_hash();
	g_table = (t_hash **)ft_xmalloc(sizeof(t_hash) * HASH_LEN);
	create_bin(getenv("PATH"));
}