/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_relat_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:26:44 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/01 18:23:50 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arifmetic.h"

size_t		expr_relat_op(void)
{
	size_t	left_value;
	size_t	right_value;
	int		type;

	left_value = expr_shift();
	if (g_error_arifmetic)
		return (0);
	while (g_lex_arif && g_lex_arif->type >= LESS_IF
			&& g_lex_arif->type <= GREAT_EQ)
	{
		type = g_lex_arif->type;
		g_lex_arif = g_lex_arif->next;
		right_value = expr_shift();
		if (g_error_arifmetic)
			return (0);
		if (type == LESS_IF)
			left_value = left_value < right_value;
		else if (type == LESS_EQ)
			left_value = left_value <= right_value;
		else if (type == GREAT_IF)
			left_value =  left_value > right_value;
		else
			left_value = left_value >= right_value;
	}
	return (left_value);
}
