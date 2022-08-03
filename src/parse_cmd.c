/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:48:37 by yalthaus          #+#    #+#             */
/*   Updated: 2022/08/03 18:48:41 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_arg(t_lstcmd *cmds, char **str, int type, char **envp)
{
	if (type == 0)
	{
		cmds->args = ft_pars_arg(str, envp);
		if (cmds->args)
			cmds->arg_init = 1;
		skip_space(str);
	}
	else if (type == 1)
	{
		cmds->redis = ft_pars_redi(str, envp);
		if (cmds->redis)
			cmds->redi_init = 1;
		skip_space(str);
	}
}
