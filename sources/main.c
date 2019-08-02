/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:11 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/02 20:41:43 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parser.h"
#include "exec.h"
// #include "get_env.h"
// #include "hash.h"
#include "lib_wtalea.h"

int			TYPE_OF_PROGRAM;

void		free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->lexeme)
		free(lex->lexeme);
	free(lex);
}

void		fill_g_hash_table(void)
{
	char			*v_path;

	v_path = NULL;
	if ((g_table = (t_hash **)ft_memalloc(sizeof(t_hash) * HASH_LEN)) == NULL)
		die_log("malloc in main");
	if ((v_path = getenv("PATH")) == NULL)
		die_log("malloc in main");
	create_bin(v_path, (t_hash ***)&g_table);
}

int			main(int ac, char **av)
{
	char		buf[1024];
	t_pars_list	*list;
	t_lex		*lex;
	t_lex		*src;
	char		*tmp;

	fill_g_hash_table();
	if (ac > 1)
	{
		if (ft_strequ(*(av + 1), "-p"))
			TYPE_OF_PROGRAM = 1;
	}
	while (1)
	{
		write(1, "sh: ", 4);
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
					ft_putendl("\nprint AST:");
					ast_print_in_order(list);
					// ft_putendl("\n\ncall exec in AST:");
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
