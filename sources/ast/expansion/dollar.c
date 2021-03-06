/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:39:09 by jterry            #+#    #+#             */
/*   Updated: 2019/10/25 16:39:54 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern t_opt	g_opt;

static void		word_not_found(char **str, int *j, int l)
{
	char	*tmp;

	while ((*str)[*j + 1] && check_spec_symbol((*str)[*j + 1])
			&& (*str)[*j + 1] != '$')
		(*j) += 1;
	tmp = ft_xstrdup(&(*str)[*j + 1]);
	(*str)[l] = '\0';
	(*str) = ft_xstrrejoin((*str), tmp, 3);
	(*j) = l - 1;
}

static void		modular_conversion(char *word, char **str, int l, int *j)
{
	char	*residue;

	residue = ft_xstrdup(&(*str)[*j + 1]);
	(*str)[l] = '\0';
	if (word)
		(*str) = ft_xstrrejoin((*str), word, 1);
	if (residue)
		(*str) = ft_xstrrejoin((*str), residue, 3);
	if (word)
	{
		*j = l + ft_strlen(word) - 1;
		free(word);
	}
}

void			dollar(int *j, char **str, t_pjobs **local)
{
	char	*word;
	int		l;
	char	*tmp;

	tmp = NULL;
	l = *j;
	if (!(word = ft_dollar_word(&(*str)[(*j) + 1], -1, j, local)) && !(str[*j]))
	{
		word_not_found(str, j, l);
		return ;
	}
	if (g_opt.arithmetic_error)
		return ;
	if ((*str)[(*j) + 1] == '$')
		(*j) += 1;
	else if ((*str)[*j + 1] == '(' && (*str)[*j + 2] == '(')
		*j += ft_strlen(*str) - ft_strlen(parser_find_dollar(*str));
	else if ((*str)[*j + 1] == '(')
		*j += ft_strlen(*str) - ft_strlen(parser_find_dollar(*str));
	else
		while ((*str)[*j + 1] && check_spec_symbol((*str)[*j + 1])
				&& (*str)[*j + 1] != '$' && (*str)[*j] != '}')
			(*j) += 1;
	modular_conversion(word, str, l, j);
}
