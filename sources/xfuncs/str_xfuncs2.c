/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_xfuncs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:24:15 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/13 12:35:13 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xfuncs.h"

void			str_xaddback(t_string *str, const char *s, size_t size)
{
	if (!str)
		return ;
	if (!(str_addback(str, s, size)))
		die();
}

void			str_xaddfront(t_string *str, const char *s, size_t size)
{
	if (!str)
		return ;
	if (!(str_addfront(str, s, size)))
		die();
}

void			str_xinsert(t_string *str, int to, const char *s, size_t size)
{
	if (!str)
		return ;
	if (!(str_insert(str, to, s, size)))
		die();
}
