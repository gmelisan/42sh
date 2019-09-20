/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterry <jterry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:14:01 by ggwin-go          #+#    #+#             */
/*   Updated: 2019/09/20 16:21:29 by jterry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		traverse_command(t_command *cmd, char **env, int in_fork, t_pjobs *local)
{
	if (cmd->simple_command)
	{
		traverse_simple_command(cmd->simple_command, env, in_fork);
	}
	else if (cmd->compound_command)
	{
		local->workgpid = 1;
		if (cmd->redirect_list)
			traverse_redirect_list(cmd->redirect_list);
		traverse_compound_command(cmd->compound_command, env, in_fork, local);
	}
	else if (cmd->function_definition)
		traverse_function_definition(cmd->function_definition, env, in_fork);
}
