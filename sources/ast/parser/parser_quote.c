/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:54:40 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/17 22:23:36 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*parser_quote(char *str, char **new_str)
{
	char	*begin;

	++str;
	begin = str;
	while (*str != '\'')
	{
		if (!*str)
		{
			*new_str = ft_strrejoin(*new_str, ft_strndup(begin, str - begin), 3);
			str = parser_recall_readline(str);
			begin = str;
		}
		else
			++str;
	}
	*new_str = ft_strrejoin(*new_str, ft_strndup(begin, str - begin), 3);
	return (str + 1);
}
