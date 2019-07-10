/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 20:45:11 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/07/10 20:15:04 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			main(void)
{
	char		buf[1024];
	t_pars_list	*list;
	t_lex		*lex;
	char		*tmp;

	ft_putstr("------------------------\n");
	while (1)
	{
		buf[read(0, &buf, 1023) - 1] = '\0';
		if (ft_strequ("exit", buf))
			break ;
		if (*(tmp = ft_strtrim(buf)))
		{
			lex = lexer(buf);
			list = parser(&lex, NULL, 0);
			ast_iter_in_order(list);
			parser_free_tree(list);
			ft_putstr("\n------------------------\n");
			free(tmp);
		}
	}
	return (0);
}
