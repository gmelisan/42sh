/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escseqs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:43:11 by gmelisan          #+#    #+#             */
/*   Updated: 2019/11/02 01:22:55 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCSEQS_H

# define ESCSEQS_H

# include "ft_readline.h"

typedef struct	s_escseq
{
	t_string	str;
	int			pos;
}				t_escseq;

/*
**t_string		get_escseq(t_string str, int *i);
*/

void			pull_escseqs(t_vector *vec, t_string *str);
t_escseq		*find_escseq(t_vector es, int n);
int				count_escseq(t_vector es, int from, int until);
void			shift_escseq(t_vector *es, int from, int count);
int				escseq_test_unmatch(t_vector v_old, t_vector v_new,
									int start, int end);

#endif
