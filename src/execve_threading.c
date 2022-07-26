/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:55:09 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 14:24:51 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**execve_arg(t_lstcmd *cmd, char **envp)
{
	int		i;
	t_list	*arg;
	char	**ret;

	i = 1;
	arg = cmd->args;
	while (cmd->arg_init && arg)
	{
		i++;
		arg = arg->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	ret[0] = cmd_exist(ft_strjoin("/", cmd->cmd), get_env("$PATH", envp));
	arg = cmd->args;
	i = 1;
	while (cmd->arg_init && arg)
	{
		ret[i++] = ft_strdup(arg->content);
		arg = arg->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	execve_threading(t_lstcmd *cmd, char **envp)
{
	char	**argv;

	argv = execve_arg(cmd, envp);
	if (argv == NULL || argv[0] == NULL)
	{
		clear_tab(argv);
		exit(1);
	}
	if (execve(argv[0], argv, envp) == -1)
		exit(1);
	clear_tab(argv);
	return ;
}
