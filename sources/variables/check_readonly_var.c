/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_readonly_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:25:03 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/23 13:53:47 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_readonly_var(const char *var, size_t name_len)
{
	if (ft_strnequ(var, "?", name_len) || ft_strnequ(var, "_", name_len) ||
			ft_strnequ(var, "SHELLOPTS", name_len) ||
			ft_strnequ(var, "NOCLOBBER", name_len) ||
			ft_strnequ(var, "SHELL_HOME", name_len) ||
			ft_strnequ(var, "SHELL_ALIASES", name_len))
	{
		((char *)var)[name_len] = '\0';
		print_error("readonly variable", var);
		return (1);
	}
	return (0);
}
