/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:41:34 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/13 15:57:24 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	check_arg_format(const char *av)
{
	const char	*tmp;
	long		res;
	char		*str;

	tmp = av;
	str = NULL;
	if (*tmp == '-' || *tmp == '+')
		++tmp;
	res = 255;
	while (*tmp)
		if (!ft_isdigit(*(tmp++)))
		{
			print_error_vaarg("exit: %s: numeric argument required\n", av);
			return (res);
		}
	if (ft_strlen(av) > 20)
		print_error_vaarg("exit: %s: numeric argument required\n", av);
	else
		res = (char)ft_atoi(av);
	return ((char)res);
}

int			ft_exit(const char **av, int ac)
{
	char		res;

	ft_putstr_fd("exit\n", 2);
	res = (char)g_res_exec;
	if (--ac > 1)
	{
		print_error("exit", "too many arguments");
		g_res_exec = 255;
		return (255);
	}
	if (av && *av)
		res = check_arg_format(*av);
	shell_clear();
	exit(res);
	return (res);
}
