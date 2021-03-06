/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wordlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <dwisoky@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 22:23:12 by dwisoky           #+#    #+#             */
/*   Updated: 2019/10/13 12:32:02 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_wordlist			*parser_free_wordlist(t_wordlist *list)
{
	if (!list)
		return (NULL);
	parser_free_wordlist(list->next);
	if (list->word)
		free(list->word);
	free(list);
	return (NULL);
}

static t_wordlist	*parser_init_wordlist(char *str)
{
	t_wordlist		*list;

	list = (t_wordlist*)ft_xmemalloc(sizeof(t_wordlist));
	g_lex = g_lex->next;
	list->next = NULL;
	list->word = str;
	return (list);
}

t_wordlist			*parser_wordlist(void)
{
	t_wordlist	*list;
	t_wordlist	*tmp;

	list = NULL;
	if (g_lex->type == WORD && ft_strequ(g_lex->lexem, "in"))
	{
		g_lex = g_lex->next;
		if (g_lex->type == WORD)
		{
			list = parser_init_wordlist(ft_xstrdup(g_lex->lexem));
			tmp = list;
			while (g_lex && g_lex->type == WORD)
			{
				tmp->next = parser_init_wordlist(ft_xstrdup(g_lex->lexem));
				tmp = tmp->next;
			}
		}
	}
	return (list);
}
