/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 01:39:35 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/06 19:11:50 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_complete_cmd			*exec_ast(char *buf)
{
	t_lex		*lex;
	t_complete_cmd	*list;

	lex = lexer(buf);
	if (!lex)
	{
		free(buf);
		return (NULL);
	}
	while (lex->back)
		lex = lex->back;
	g_lex = lex;
	g_error_lex = NULL;
	list = parser();
	if (g_error_lex)
	{
		printf("%d\n", g_error_lex->type);
		return (parser_free(list));
	}
	lexer_free_all(lex);
	return (list);
}
