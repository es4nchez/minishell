/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:53:22 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 12:53:10 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_waitpid(t_lstcmd *cmds)
{
	int	ret;

	while (cmds)
	{
		if (cmds->pid != 0)
			waitpid(cmds->pid, &ret, 0);
		cmds = cmds->next;
		if (WIFEXITED(ret))
			g_retcmd = WEXITSTATUS(ret);
	}
}

void	builtins(t_input *input, t_lstcmd *cmds, char **envp)
{
	if (!cmds || !cmds->cmd)
		return ;
	if (!ft_strncmp(cmds->cmd, "echo", 4))
		bt_echo(cmds);
	//else if (!ft_strncmp(cmds->cmd, "cd", 2));
		//bt_cd(envp, ft_split(lineread, ' ')[1]);
	else if (!ft_strncmp(cmds->cmd, "exit", 4))
		bt_exit(input);
	else if (!ft_strncmp(cmds->cmd, "pwd", 3))
		bt_pwd(envp);
	else if (!ft_strncmp(cmds->cmd, "env", 3))
		bt_env(envp);
	//else if (!ft_strncmp(cmds->cmd, "export", 6));
		//bt_export(envp, lineread);
	//else if (!ft_strncmp(cmds->cmd, "unset", 5));
		//bt_unset(envp, lineread);
	else
		execve_threading(cmds, envp);
}

void	child_process(t_input *input, char **envp, t_lstcmd *cmds)
{
	if (cmds->redi_init)
		exec_redirect(check_redirect(cmds->redis), cmds->redis, input);
	if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
		pipe_r(input);
	builtins(input, cmds, envp);
}

int	exec_process(t_input *input, char **envp, t_lstcmd *cmds)
{
	if (cmds->pid == 0)
		child_process(input, envp, cmds);
	else
	{
		if (cmds && !cmds->next && !ft_strncmp(cmds->cmd, "exit", 4))
			exit(0);
		else if (cmds && cmds->next && !ft_strncmp(cmds->cmd, "exit", 4))
			return (1);
		if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
			pipe_w(input);
	}
	return (0);
}

void	execution(t_input *input, char **envp)
{
	t_lstcmd	*cmds;

	cmds = input->cmds;
	while (cmds && cmds->cmd)
	{
		if (cmds->next)
			if (pipe(input->pipe_fd) == -1)
				return ;
		cmds->pid = fork();
		if (exec_process(input, envp, cmds))
			break ;
		if (cmds->next && cmds->next->next)
			cmds = cmds->next->next;
		else
			cmds = NULL;
	}
	ft_waitpid(input->cmds);
	reset_std(input);
}
