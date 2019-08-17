/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 14:16:54 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/08/17 06:08:44 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	replace_var(const char *name, const char *var, char **env,
															size_t len)
{
	while (*env && !(ft_strnequ(name, *env, len) && *(*env + len) == '='))
		++env;
	if (*env)
	{
		free(*env);
		*env = ft_xstrdup(var);
	}
	return (0);
}
