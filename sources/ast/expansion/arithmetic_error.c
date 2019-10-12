/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:19:40 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/12 19:42:07 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arifmetic.h"

void			arithmetic_error_norma(t_lex *begin)
{
	while (begin->next)
		begin = begin->next;
	ft_putstr_fd(begin->lexem, 2);
}

void			*arithmetic_error(char *str, t_lex *begin)
{
	if (g_error_arifmetic->type == DIVISION_NULL)
		print_error_vaarg("%s: division by 0 ", str);
	else if (g_error_arifmetic->type >= 3 && g_error_arifmetic->type <= 12)
		print_error_vaarg("%s: attempted assignment to non-variable ", str);
	else
		print_error_vaarg("%s: syntax error: operand expected", str);
	ft_putstr_fd("(error token is \"", STDERR);
	if (g_error_arifmetic->type == DIVISION_NULL)
		lexer_free_all(g_error_arifmetic);
	if (!g_lex_arif)
		arithmetic_error_norma(begin);
	while (g_lex_arif)
	{
		ft_putstr_fd(g_lex_arif->lexem, 2);
		if (g_lex_arif->next)
			ft_putstr_fd(" ", 2);
		g_lex_arif = g_lex_arif->next;
	}
	ft_putendl_fd("\")", 2);
	free(str);
	lexer_free_all(begin);
	return (NULL);
}

char			*arithmetic_print_lex_error(char *str)
{
	print_error_vaarg("%s: syntax error: operand expected "
			"(error token is \"%s\")\n", str, g_error_arifmetic->lexem);
	lexer_free_all(g_error_arifmetic);
	lexer_free_all(g_lex_arif);
	free(str);
	return (NULL);
}
