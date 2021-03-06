/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function_body.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:39:37 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/05 20:42:34 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Grammar rule
** function_body    : compound_command                 Apply rule 9
**                  | compound_command redirect_list   Apply rule 9
**                  ;
*/

t_function_body				*parser_free_function_body(t_function_body *list)
{
	if (!list)
		return (NULL);
	parser_free_compound_command(list->compound_command);
	parser_free_redirect_list(list->redirect_list);
	free(list);
	return (NULL);
}

static t_function_body		*parser_init_function_body(void)
{
	t_function_body			*list;

	list = (t_function_body*)ft_xmemalloc(sizeof(t_function_body));
	list->compound_command = NULL;
	list->redirect_list = NULL;
	return (list);
}

t_function_body				*parser_function_body(void)
{
	t_function_body	*list;

	list = parser_init_function_body();
	list->compound_command = parser_compound_command();
	if (!list->compound_command && !g_error_lex)
		g_error_lex = g_lex;
	if (g_error_lex)
		return (parser_free_function_body(list));
	list->redirect_list = parser_redirect_list(NULL);
	return (list);
}
