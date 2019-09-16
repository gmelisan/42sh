/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:26:34 by gmelisan          #+#    #+#             */
/*   Updated: 2019/09/16 15:38:21 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fc.h"

static int	count_len(const char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	show_usage(void)
{
	ft_fdprintf(STDERR,
				"fc: usage: fc [-e ename] [-lrn] [first] [last] or "
				"fc -s [pat=rep] [command]\n");
	ft_getopt_clear();
	return (1);
}

static void	run_fc(t_cmd_opt opt)
{
	if (opt.l)
		ft_fc_list(opt);
}

int			ft_fc(const char **argv)
{
	int			argc;
	int			o;
	t_cmd_opt	opt;

	ft_bzero(&opt, sizeof(opt));
	argc = count_len(argv);
	ft_getopt_init("fc");
	while (argv[g_optind] && !ft_isdigit(argv[g_optind][1]) &&
				(o = ft_getopt(argc, (char *const *)argv, "lnrse:")) != -1)
		if (o == 'l')
			opt.l = 1;
		else if (o == 'n')
			opt.n = 1;
		else if (o == 'r')
			opt.r = 1;
		else if (o == 's')
			opt.s = 1;
		else if (o == 'e')
			opt.e = 1;
		else if (o == '?')
			return (show_usage());
	run_fc(opt);
	ft_getopt_clear();
	return (0);
}