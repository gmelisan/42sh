/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:26:54 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/10/30 22:51:33 by ggwin-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		check_file_errors(const char *file_name, int flag)
{
	struct stat		st;
	extern t_opt	g_opt;
	char			*error;

	if ((stat(file_name, &st) == -1 && (error = "No such file or directory"))
			|| (S_ISDIR(st.st_mode) && (error = "Is a directory"))
			|| (!S_ISREG(st.st_mode) && (error = "No such file or directory")))
	{
		print_error(file_name, error);
		return ((g_res_exec = 127));
	}
	else if (access(file_name, flag) && (error = "Permission denied"))
	{
		print_error(file_name, error);
		return ((g_res_exec = 126));
	}
	return (0);
}
