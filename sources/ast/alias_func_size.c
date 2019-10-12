/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_func_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:43:31 by wtalea            #+#    #+#             */
/*   Updated: 2019/10/12 20:02:29 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "dictionary.h"

extern	t_alias	*g_alias;

int		func_size_list(t_dict *func)
{
	int		i;

	i = 0;
	while (func)
	{
		if (!get_bin(func->key))
			++i;
		func = func->next;
	}
	return (i);
}

int		alias_size_list(t_alias *alias)
{
	int		i;

	i = 0;
	while (alias)
	{
		if (!get_bin(alias->head))
			++i;
		alias = alias->next;
	}
	return (i);
}