/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 22:36:04 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/09 15:41:59 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "sh.h"

int		check_file_errors(const char *file_name, int flag);
void	print_error(const char *info, const char *msg);
void	print_error_vaarg(const char *msg, ...);
void	print_error_ext(const char *msg, const char *info1, const char *info2);
void	print_error_exit(const char *msg, const char *info, int code);
void	fatal(const char *msg);

#endif
