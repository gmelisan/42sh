/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:11 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/03 17:59:30 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parser.h"
#include "exec.h"
// #include "get_env.h"
// #include "hash.h"

int			TYPE_OF_PROGRAM;

void		free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->lexeme)
		free(lex->lexeme);
	free(lex);
}

int			main(int ac, char **av)
{
	char		buf[1024];
	t_pars_list	*list;
	t_lex		*lex;
	t_lex		*src;
	char		*tmp;

	fill_hash_table();
	if (ac > 1)
	{
		if (ft_strequ(*(av + 1), "-p"))
			TYPE_OF_PROGRAM = 1;
	}
	while (1)
	{
		ft_putstr("\033[0;34msh:\033[0m ");
		buf[read(0, &buf, 1023) - 1] = '\0';
		if (ft_strequ("exit", buf))
			break ;
		if (*(tmp = ft_strtrim(buf)))
		{
			lex = lexer(buf);
			src = lex;
			while (src->next)
				src = src->next;
			list = parser(lex, NULL, 0);
			if (!g_error_pars)
			{
				if (TYPE_OF_PROGRAM)
				{
					ft_putendl("print AST:");
					ast_print_in_order(list);
					ft_putstr("\n");
				}
				else
					ast_exec(list);
			}
			g_error_pars = 0;
			parser_free_tree(list);
			while (src->prev)
			{
				lex = src;
				src = src->prev;
				free_lex(lex);
			}
			free_lex(src);
			free(tmp);
			int i = 0;
			while (i < 1023)
				buf[i++] = '\0';
		}
	}
	del_hash(&g_table);
	return (0);
}
