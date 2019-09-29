/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_hendler_plus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 17:58:57 by jterry            #+#    #+#             */
/*   Updated: 2019/09/29 20:54:25 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*buf_finder(char *tmp)
{
	char	*buf;

	if ((buf = get_var_value(tmp)) == NULL)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	if ((buf) == NULL)
		return (0);
	return (buf);
}

static char	*next_char_check(char *str, int *j)
{
	if (*str && *str == '$')
		return (ft_strdup(ft_itoa(getpid())));
	else if (*str && *str == '{')
		return (brace_handler(str + 1, j));
	else
		return (NULL);
}

char		*ft_dollar_word(char *str, int k, int *j)
{
	char	*tmp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if ((tmp = next_char_check(str, j)))
		return (tmp);
	else
		while (str[i] && check_spec_symbol(str[i]) && str[i] != '$')
			i++;
	tmp = (char *)ft_xmalloc(sizeof(char) * (i + 1));
	while (++k < i)
		tmp[k] = str[k + flag];
	tmp[k] = '\0';
	return (ft_strdup(buf_finder(tmp)));
}
