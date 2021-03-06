/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   possible_filename_completions.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 07:48:28 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/19 15:26:06 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "del_funcs.h"

void			possible_filename_completions(t_line *line)
{
	t_vector	vec;

	vec = filter_filenames(line);
	if (vec.len != 1)
		show_completions(vec.v, vec.len);
	vec_delete(&vec, del_str);
}
