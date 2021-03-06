/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:30:19 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/24 18:39:37 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xfuncs.h"
#include "terminal.h"

void		die(void)
{
	fatal("Out of virtual memory");
	exit(1);
}

void		*ft_xmalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
		die();
	return (ptr);
}

void		*ft_xmemalloc(size_t size)
{
	void *ptr;

	ptr = ft_memalloc(size);
	if (!ptr)
		die();
	return (ptr);
}
