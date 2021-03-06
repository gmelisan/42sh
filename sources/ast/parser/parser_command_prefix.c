/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_prefix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <dwisoky@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:12:39 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/13 12:30:19 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char			*parser_check_assignment_word(void)
{
	char			*tmp;

	if (!g_lex)
		return (NULL);
	if (g_lex->type == WORD)
	{
		tmp = g_lex->lexem;
		while (*tmp)
		{
			if (*tmp == '"' || *tmp == '\'' || *tmp == '\\')
				tmp = lexer_find_char(tmp, *tmp);
			else if (*tmp == '=')
			{
				tmp = parser_word_expansion(g_lex->lexem);
				g_lex = g_lex->next;
				return (tmp);
			}
			else
				++tmp;
		}
	}
	return (NULL);
}

t_cmd_prefix		*parser_free_cmd_prefix(t_cmd_prefix *list)
{
	if (!list)
		return (NULL);
	if (list->assignment_word)
		free(list->assignment_word);
	parser_free_io_redirect(list->io_redir);
	parser_free_cmd_prefix(list->cmd_pref);
	free(list);
	return (NULL);
}

static t_cmd_prefix	*parser_init_cmd_prefix(void)
{
	t_cmd_prefix	*list;

	list = (t_cmd_prefix*)ft_xmemalloc(sizeof(t_cmd_prefix));
	list->io_redir = NULL;
	list->assignment_word = NULL;
	return (list);
}

t_cmd_prefix		*parser_cmd_prefix(void)
{
	t_cmd_prefix	*list;

	if (!g_lex)
		return (NULL);
	list = parser_init_cmd_prefix();
	if (!(list->assignment_word = parser_check_assignment_word()))
		if (!(list->io_redir = parser_io_redirect()))
			return (parser_free_cmd_prefix(list));
	if (g_error_lex)
		return (parser_free_cmd_prefix(list));
	list->cmd_pref = parser_cmd_prefix();
	return (list);
}
