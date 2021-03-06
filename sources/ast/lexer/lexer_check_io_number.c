/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_io_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <dwisoky@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 20:13:28 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/13 12:29:33 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char		*lexer_check_io_number(char *str, t_lex **lex)
{
	char	*begin;

	begin = str;
	while (*str && *str >= '0' && *str <= '9')
		++str;
	if (*str == '>' || *str == '<' || (*str == '&' && *(str + 1) != '&'))
	{
		init_lex(IO_NUMBER, ft_xstrndup(begin, str - begin), lex);
		--str;
	}
	else
		str = lexer_find_word(begin, lex);
	return (str);
}
