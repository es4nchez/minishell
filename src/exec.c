/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:53:22 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/24 19:53:24 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(t_lstcmd *cmds, char **envp)
{
	if (!cmds || !cmds->cmd)
		return ;
	if (!ft_strncmp(cmds->cmd, "echo", 4))
		bt_echo(cmds);
	else if (!ft_strncmp(cmds->cmd, "cd", 2));
	 	//bt_cd(envp, ft_split(lineread, ' ')[1]);
	else if (!ft_strncmp(cmds->cmd, "exit", 4));
		//bt_exit(input);
	else if (!ft_strncmp(cmds->cmd, "pwd", 3))
		bt_pwd(envp);
	else if (!ft_strncmp(cmds->cmd, "env", 3))
		bt_env(envp);
	else if (!ft_strncmp(cmds->cmd, "export", 6));
	 	//bt_export(envp, lineread);
	else if (!ft_strncmp(cmds->cmd, "unset", 5));
		//bt_unset(envp, lineread);
	else
	 	execve_threading(cmds, envp);
	exit(0);
}

void	execution(t_input *input, char **envp)
{
	t_lstcmd	*cmds;
	int			redi;
	pid_t		pid;

	cmds = input->cmds;
	while (cmds)
	{
		redi = 0;
		redi = check_redirect(cmds);
		pid = fork();
		if (pid == 0)
		{
			if (redi > 0)
				fd_process(redi, cmds);
			builtins(cmds, envp);
		}
		else
			wait(NULL);
		if (redi != -1 && !cmds->next->next)
			cmds = cmds->next->next;
		else
			cmds = NULL;
	}
}
