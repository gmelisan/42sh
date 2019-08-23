/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:11 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/23 17:26:12 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "parser.h"
#include "exec.h"
// #include "get_env.h"
// #include "hash.h"

/*
 **	variable for launch shell with param
 (now using for print ast instead for exec cmd).
 */

int			TYPE_OF_PROGRAM;

/*
 **	global variable for internal shell variables.
 */

char		**g_var;
char		**g_var_names;

t_pars_list	*ast_treatment_error(char *buf)
{
	char	*tmp;

	buf = ft_strrejoin(buf, "\n", 1);
	tmp = buf;
	buf = ft_readline("> ", tmp);
	free(tmp);
	ft_putstr("\n");
	g_error_pars = 0;
	return (exec_ast(buf));
}

t_pars_list	*exec_ast(char *buf)
{
	t_lex		*lex;
	t_lex		*src;
	t_pars_list	*list;

	lex = lexer(buf);
	src = lex;
	while (src->next)
		src = src->next;
	list = parser(lex, NULL, 0);
	check_quotes(buf);
	lexer_free_all(src);
	if (g_error_pars == 1)
		return (parser_free_tree(list));
	if (g_error_pars == 2)
	{
		parser_free_tree(list);
		return (ast_treatment_error(buf));
	}
	free(buf);
	return (list);
}

int			main(int ac, char **av)
{
	char		*buf;
	t_pars_list	*list;
	//	t_lex		*lex;
	//	t_lex		*src;
	char		*tmp;
	extern char	**environ;

	preliminary_check_fd();
	environ = create_copy_env(environ);
	init_g_var();
	fill_g_var_names();
	fill_hash_table();
	logopen();
	g_history = ft_xmemalloc(sizeof(t_history));
	history_load(g_history);
	g_rl_options.enable_color = 1;
	if (ac > 1)
	{
		if (ft_strequ(*(av + 1), "-p"))
			TYPE_OF_PROGRAM = 1;
		else if (ft_strequ(*(av + 1), "-v"))
			g_rl_options.vi_mode = 1;
	}
	while (1)
	{
		buf = ft_readline(get_value_from_all_vars("PS1"), NULL);
		if (g_errno)
			printerr();
		if (!buf)
			break ;
		else
		{
			ft_putstr("\n");
			if (*(tmp = ft_strtrim(buf)))
			{
				list = exec_ast(buf);
				if (TYPE_OF_PROGRAM)
				{
					ft_putendl("print AST:");
					print_ast(list);
					ft_putstr("\n");
				}
				else
					traverse_ast(list);
				g_error_pars = 0;
				parser_free_tree(list);
			}
			else
				free(buf);
			free(tmp);
		}
	}
	del_hash();
	history_clear(g_history);
	logclose();
	ft_free_double_ptr_arr((void ***)&environ);
	ft_putstr("exit\n");
	return (g_res_exec);
}
