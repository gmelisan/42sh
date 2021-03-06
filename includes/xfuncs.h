/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfuncs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 05:55:27 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/24 18:25:19 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFUNCS_H
# define XFUNCS_H

# include "libft.h"
# include "ft_string.h"
# include "ft_vector.h"

void		die(void);
void		*ft_xmalloc(size_t size);
void		*ft_xmemalloc(size_t size);
char		*ft_xstrdup(const char *src);
char		*ft_xstrndup(const char *src, size_t j);
char		*ft_xstrjoin(char const *s1, char const *s2);
char		**ft_xstrsplit(char const *s, char c);
char		*ft_xstrtrim(char const *s);
char		*ft_xstrrejoin(char const *s1, char const *s2, int numstr_to_free);

t_string	str_xcreate(size_t len);
t_string	str_xduplicate(t_string str);
t_string	str_xcopy(const char *s);
t_string	str_xncopy(const char *s, int n);
t_string	str_xsubstring(t_string str, int start, int len);
void		str_xaddback(t_string *str, const char *s, size_t size);
void		str_xaddfront(t_string *str, const char *s, size_t size);
t_string	*str_xinsert(t_string *str, int to, const char *s, size_t size);
t_string	*str_xreplace(t_string *str, const char *what, const char *with);

t_vector	vec_xcreate(size_t len, size_t size);
t_vector	vec_xduplicate(t_vector vec, void *(*duplicate)(void *));
void		vec_xaddback(t_vector *vec, void *new);
void		vec_xaddfront(t_vector *vec, void *new);

#endif
