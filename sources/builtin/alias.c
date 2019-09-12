/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwisoky <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:24:42 by dwisoky           #+#    #+#             */
/*   Updated: 2019/09/12 22:23:09 by dwisoky          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			alias_free_all(void)
{
	t_alias			*tmp;
	extern t_alias	*g_alias;

	while (g_alias)
	{
		if (g_alias->head)
			free(g_alias->head);
		if (g_alias->body_alias)
			free(g_alias->body_alias);
		tmp = g_alias->next;
		free(g_alias);
		g_alias = tmp;
	}
}

static t_alias	*alias_init(char *head, char *body)
{
	t_alias		*list;

	list = (t_alias*)ft_xmalloc(sizeof(t_alias));
	list->head = head;
	list->body_alias = body;
	return (list);
}

static int		alias_set_str(const char *str, t_alias *tmp, t_alias **begin)
{
	char			*head;
	char			*body;

	if (!(body = ft_strchr(str, '=')))
		return (0);
	head = ft_strndup(str, body - str);
	body = ft_xstrdup(body + 1);
	while (tmp)
	{
		if (ft_strequ(head, tmp->head))
		{
			free(head);
			free(tmp->body_alias);
			tmp->body_alias = body;
			return (1);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = alias_init(head, body);
	else
		*begin = alias_init(head, body);
	return (1);
}

static int		alias_print_str(const char *str)
{
	extern char		*g_project_name;
	extern t_alias	*g_alias;
	t_alias			*tmp;

	tmp = g_alias;
	while (tmp)
	{
		if (ft_strequ(tmp->head, str))
		{
			ft_putstr("alias ");
			ft_putstr(tmp->head);
			ft_putstr("='");
			ft_putstr(tmp->body_alias);
			ft_putstr("'\n");
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putstr_fd(g_project_name, 2);
	ft_putstr_fd(": alias: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not found\n", 2);
	return (1);
}

int				alias(const char **av)
{
	extern t_alias	*g_alias;
	t_alias			*tmp_alias;
	int				return_value;
	int				tmp;

	return_value = 0;
	tmp = 0;
	tmp_alias = g_alias;
	if (!*av)
		while (tmp_alias)
		{
			alias_print_str(tmp_alias->head);
			tmp_alias = tmp_alias->next;
		}
	while (*av)
	{
		if (!(tmp = alias_set_str(*av, tmp_alias, &g_alias)))
			tmp = alias_print_str(*av);
		if (!return_value)
			return_value = tmp;
		++av;
	}
	return (0);
}
