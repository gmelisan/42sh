/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 22:31:52 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/02 17:15:42 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arifmetic.h"

size_t		expr_check_type(size_t var_value, int type, size_t value)
{
	if (!g_error_arifmetic &&
			(type == DIV_ASSIGNMENT || type == MOD_ASSIGNMENT) && value == 0)
		init_lex(DIVISION_NULL, NULL, &g_error_arifmetic);
	if (g_error_arifmetic)
		return (0);
	if (type == ASSIGNMENT)
		return (value);
	else if (type == ADD_ASSIGNMENT)
		return (var_value + value);
	else if (type == MIN_ASSIGNMENT)
		return (var_value - value);
	else if (type == MUL_ASSIGNMENT)
		return (var_value * value);
	else if (type == DIV_ASSIGNMENT)
		return (var_value / value);
	else if (type == MOD_ASSIGNMENT)
		return (var_value % value);
	else if (type == DLS_ASSIGNMENT)
		return (var_value << value);
	else if (type == DGR_ASSIGNMENT)
		return (var_value >> value);
	else if (type == AND_ASSIGNMENT)
		return (var_value & value);
	else
		return (var_value | value);
}

size_t		expr(void)
{
	extern char	**g_var;
	size_t		value;
	size_t		var_value;
	char		*var;
	int			type;

	if (g_lex_arif && g_lex_arif->type == VAR && g_lex_arif->next
			&& g_lex_arif->next->type >= ASSIGNMENT
			&& g_lex_arif->next->type <= OR_ASSIGNMENT)
	{
		var = g_lex_arif->lexem;
		var_value = expr_get_var_value();
		type = g_lex_arif->type;
		g_lex_arif = g_lex_arif->next;
		value = expr();
		value = expr_check_type(var_value, type, value);
		if (g_error_arifmetic)
			return (0);
		var = ft_strjoin(var, "=");
		var = ft_strrejoin(var, ft_itoa_base(value, 10), 3);
		set_var(var, &g_var, 0);
		free(var);
		return (value);
	}
	return (expr_or());
}
