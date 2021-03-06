/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <dwisoky@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:29:18 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/21 20:28:20 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Grammar rule
** pipe_sequence    :                             command
**                  | pipe_sequence '|' linebreak command
**                  ;
*/

t_pipe_sequence		*parser_free_pipe_sequence(t_pipe_sequence *list)
{
	if (!list)
		return (NULL);
	parser_free_command(list->command);
	parser_free_pipe_sequence(list->next);
	free(list);
	return (NULL);
}

t_pipe_sequence		*parser_init_pipe_sequence(void)
{
	t_pipe_sequence	*list;

	list = (t_pipe_sequence*)ft_xmemalloc(sizeof(t_pipe_sequence));
	list->next = NULL;
	list->pipe_op = 0;
	list->lex_begin = g_lex;
	list->lex_end = NULL;
	list->command = NULL;
	return (list);
}

t_pipe_sequence		*parser_pipe_sequence(void)
{
	t_pipe_sequence	*list;

	list = parser_init_pipe_sequence();
	list->command = parser_command();
	if (!g_lex)
	{
		list->lex_end = g_lex;
		return (list);
	}
	if (g_error_lex)
		return (parser_free_pipe_sequence(list));
	if (g_lex->type == PIPE)
	{
		list->pipe_op = 1;
		g_lex = g_lex->next;
		parser_linebreak();
		list->next = parser_pipe_sequence();
	}
	list->lex_end = g_lex;
	return (list);
}
