/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_double_dote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:34:31 by jterry            #+#    #+#             */
/*   Updated: 2019/10/27 21:45:07 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern t_opt	g_opt;
extern char		**g_var;

static char		*dd_qwest(char *str, char *value, char *name)
{
	value = value_rep(&str[2]);
	if (g_opt.rl_gnl == 1)
		ft_exit(0, NULL);
	else if (value == NULL)
		print_error("parameter null or not set", name);
	else
		print_error(name, value);
	free(value);
	return (NULL);
}

static char		*dd_equal(char *str, char *value, char *name)
{
	value = ft_xstrrejoin(name, "=", 0);
	value = ft_xstrrejoin(value, value_rep(&str[2]), 1);
	set_var(value, &g_var, 0);
	return (value_rep(&str[2]));
}

char			*double_dote(char *str, char *value, char *buf, char *name)
{
	if (str[1] == '-')
	{
		if (buf == NULL)
			return (value_rep(&str[2]));
	}
	else if (str[1] == '=')
	{
		if (buf == NULL)
			return (dd_equal(str, value, name));
	}
	else if (str[1] == '+')
	{
		if (buf)
			return (value_rep(&str[2]));
		else
			return (NULL);
	}
	else if (str[1] == '?')
	{
		if (!buf)
			return (dd_qwest(str, value, name));
	}
	g_opt.arithmetic_error = 1;
	print_error_vaarg("unrecognized modifier `%c'\n", str[1]);
	return (NULL);
}
