#include "parser.h"

t_cmd_suffix		*parser_free_cmd_suffix(t_cmd_suffix *list)
{
	if (!list)
		return (NULL);
	parser_free_io_redirect(list->io_redir);
	parser_free_cmd_suffix(list->cmd_suf);
	if (list->word)
		free(list->word);
	free(list);
	return (NULL);
}

static t_cmd_suffix	*parser_init_cmd_suffix(void)
{
	t_cmd_suffix	*list;

	list = (t_cmd_suffix*)ft_xmalloc(sizeof(t_cmd_suffix));
	list->cmd_suf = NULL;
	list->io_redir = NULL;
	list->word = NULL;
	return (list);
}

t_cmd_suffix	*parser_cmd_suffix(void)
{
	t_cmd_suffix	*list;

	if (!g_lex)
		return (NULL);
	list = parser_init_cmd_suffix();
	if (g_lex->type != WORD)
	{
		if (!(list->io_redir = parser_io_redirect())) //изменить на io_redirect
				return (parser_free_cmd_suffix(list));
	}
	else
	{
		list->word = ft_strdup(g_lex->lexem);
		g_lex = g_lex->next;
	}
	if (g_error_lex)
		return (parser_free_cmd_suffix(list));
	list->cmd_suf = parser_cmd_suffix();
	return (list);
}
