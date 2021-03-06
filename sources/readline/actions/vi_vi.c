/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_vi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 09:00:56 by gmelisan          #+#    #+#             */
/*   Updated: 2019/10/25 16:35:49 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

static char	**build_argv(char *str)
{
	char	**argv;

	argv = ft_xmemalloc(sizeof(char *) * 3);
	argv[0] = ft_xstrdup(get_var_value("TEXTEDITOR"));
	if (!argv[0])
		argv[0] = ft_xstrdup(DEFAULT_TEXTEDITOR);
	argv[1] = ft_xstrdup(str);
	return (argv);
}

static void	free_argv(char **argv)
{
	ft_strdel(&argv[0]);
	ft_strdel(&argv[1]);
	free(argv);
}

static void	start_vi(char **argv)
{
	pid_t		pid;
	extern char	**environ;
	t_pjobs		*local;

	local = jobs_started(ft_xstrdup("vi mode"), 0);
	if ((pid = fork()) < 0)
	{
		setpgid(getpid(), getpid());
		tcsetpgrp(0, getpid());
		loginfo("vi_vi(): fork error");
		return ;
	}
	local = ljobs_started(ft_xstrdup("vi mode"), local->flag, local->num, pid);
	if (pid == 0 && execve(argv[0], argv, environ) < 0)
		loginfo("vi_vi(): execve error");
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	ft_waitpid(pid, NULL);
}

static void	read_file(int fd, t_line *line)
{
	char		*s;
	t_string	str;
	int			ret;

	s = NULL;
	str = str_xcreate(0);
	while ((ret = get_next_line(fd, &s)) > 0)
	{
		if (*s)
		{
			str_addback(&str, s, ft_strlen(s));
			str_addback(&str, "\n", 1);
		}
		ft_strdel(&s);
	}
	if (str_get(str, str.len - 1) == '\n')
		str_remove(&str, str.len - 1, 1);
	if (ret < 0)
		loginfo("vi_vi(): gnl error");
	else
	{
		str_delete(line->str);
		*line->str = str;
	}
}

void		vi_vi(t_line *line)
{
	int		fd;
	char	**argv;

	fd = open(TMP_PATH, O_RDWR | O_CREAT | O_TRUNC,
				S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
	{
		loginfo("vi_vi(): open error (%s)", TMP_PATH);
		return ;
	}
	ft_putstr_fd(line->str->s, fd);
	close(fd);
	argv = build_argv(TMP_PATH);
	start_vi(argv);
	free_argv(argv);
	fd = open(TMP_PATH, O_RDWR, S_IRWXU);
	read_file(fd, line);
	close(fd);
	unlink(TMP_PATH);
}
