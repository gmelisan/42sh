/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggwin-go <ggwin-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:35:39 by gmelisan          #+#    #+#             */
/*   Updated: 2019/08/19 16:22:38 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <dirent.h>

# include "libft.h"
# include "ft_string.h"
# include "ft_vector.h"

# include "sh.h"
# include "line.h"
# include "ft_errno.h"
# include "terminal.h"
# include "keys.h"
# include "bindings.h"
# include "display.h"
# include "signal_handlers.h"
# include "actions.h"
# include "history.h"
# include "history_search.h"
# include "input_loop.h"
# include "escseqs.h"
# include "loginfo.h"
# include "utils.h"
# include "undo.h"
# include "go_history.h"

# define DEBUG				1

# define VI_INSERT			1
# define VI_COMMAND			2

struct 			s_rl_options
{
	t_uint		vi_mode;
}				g_rl_options;

char			*ft_readline(char *prompt, char *oldline);
void			del_undo_one(void *p, size_t i);

#endif
