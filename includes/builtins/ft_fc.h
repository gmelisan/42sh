/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:12:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/16 14:41:43 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FC_H
# define FT_FC_H

# include "builtins.h"

typedef struct	s_cmd_opt
{
	t_uint e : 1;
	t_uint l : 1;
	t_uint n : 1;
	t_uint r : 1;
	t_uint s : 1;
}				t_cmd_opt;

void	ft_fc_list(t_cmd_opt opt);

#endif