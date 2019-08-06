/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 18:28:20 by ggwin-go          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/13 17:00:06 by dwisoky          ###   ########.fr       */
=======
/*   Updated: 2019/06/19 11:44:33 by ggwin-go         ###   ########.fr       */
>>>>>>> 27c6c979f3ea52cc9e0293d43341b7db5e0c38c5
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

t_exec	*init_exec(int count, char **av, int ispipe)
{
	t_exec	*exec;
	int		i;

	exec = (t_exec*)ft_xmalloc(sizeof(t_exec));
	exec->av = (char**)ft_xmalloc(sizeof(char*) * (count + 1));
	i = 0;
	while (*av)
	{
		exec->av[i] = ft_strdup(*av);
		++av;
		i++;
	}
	exec->ispipe = ispipe;
	exec->av[i] = NULL;
	exec->attr = NULL;
	exec->next = NULL;
	return (exec);
}