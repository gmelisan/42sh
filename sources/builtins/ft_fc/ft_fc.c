/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelisan <gmelisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:26:34 by gmelisan          #+#    #+#             */
/*   Updated: 2019/11/02 20:02:57 by gmelisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fc.h"

static int	show_usage(void)
{
	ft_fdprintf(STDERR,
				"fc: usage: fc [-e ename] [-lrn] [first] [last] or "
				"fc -s [pat=rep] [command]\n");
	ft_getopt_clear();
	return (1);
}

static int	run_fc(const char **argv, t_cmd_opt opt, t_pjobs **local)
{
	int		ret;

	ret = 0;
	if (opt.s)
		ret = ft_fc_reexec(argv, local);
	else if (opt.l)
		ret = ft_fc_list(argv, opt);
	else
		ret = ft_fc_edit(argv, opt, local);
	return (ret);
}

static int	fill_opt(t_cmd_opt *opt, int o)
{
	if (o == 'l')
		opt->l = 1;
	else if (o == 'n')
		opt->n = 1;
	else if (o == 'r')
		opt->r = 1;
	else if (o == 's')
		opt->s = 1;
	else if (o == 'e')
		opt->e = 1;
	else if (o == '?')
		return (show_usage());
	return (0);
}

int			ft_fc(int argc, const char **argv, t_pjobs **local)
{
	int			o;
	t_cmd_opt	opt;
	int			ret;

	ft_bzero(&opt, sizeof(opt));
	ft_getopt_init("fc");
	while (argv[g_optind] && !ft_isdigit(argv[g_optind][1]) &&
				(o = ft_getopt(argc, (char *const *)argv, "lnrse:")) != -1)
		if (fill_opt(&opt, o) == 1)
			return (1);
	ret = run_fc(argv, opt, local);
	ft_getopt_clear();
	return (ret);
}
