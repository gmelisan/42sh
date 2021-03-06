/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_xinsert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:24:15 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/23 20:39:48 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xfuncs.h"

t_string	*str_xinsert(t_string *str, int to, const char *s, size_t size)
{
	t_string	*p;

	if (!str || !s || !size)
		return (str);
	if (!(p = str_insert(str, to, s, size)))
		die();
	return (p);
}
