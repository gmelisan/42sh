/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:02:15 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/21 20:45:07 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*parser_fill_test(void)
{
	char	*tmp;

	tmp = ft_strdup("[[ ");
	g_lex = g_lex->next;
	
}