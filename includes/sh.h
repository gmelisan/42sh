/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:44:12 by dwisoky           #+#    #+#             */
/*   Updated: 2019/11/02 16:59:47 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <sys/wait.h>
# include <pwd.h>
# include "defs.h"
# include "libft.h"
# include "error.h"
# include "ast.h"
# include "lexer.h"
# include "hash.h"
# include "ft_readline.h"
# include "variables.h"
# include "xfuncs.h"
# include "jobs.h"
# include "builtins.h"
# include "expansion.h"
# include "dictionary.h"

# ifdef __APPLE__
#  include <mach-o/loader.h>
# else
#  define MH_MAGIC		0x464c457f
#  define MH_MAGIC_64	0x464c457f
# endif

typedef struct		s_opt
{
	t_uint			vi_mode;
	t_uint			emacs_mode;
	t_uint			enable_color;
	t_uint			noclobber;
	t_uint			history;
	t_uint			promptsp;
	t_uint			rl_in;
	t_uint			rl_out;
	t_uint			rl_gnl;
	t_uint			is_subshell;
	t_uint			is_single_cmd;
	t_uint			arithmetic_error;
}					t_opt;

typedef struct		s_alias
{
	struct s_alias	*next;
	char			*head;
	char			*body_alias;
}					t_alias;

void				signal_monitor();
void				sigh_exit(int signo);
void				shell_init(int ac, char **av);
int					check_binary(char *path);
void				shell_clear(void);
void				print_exit(void);
void				execute_line(char *buf);
void				fill_g_cmd_names(void);
t_complete_cmd		*exec_ast(char *buf, t_lex **lex);

int					alias_size_list(t_alias *alias);
int					func_size_list(t_dict *func);

void				ft_nanosleep(long sec, long nsec);

#endif
