/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:53:22 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/26 13:43:57 by yalthaus         ###   ########.fr       */
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

void	builtins(t_input *input, t_lstcmd *cmds, char ***envp)
{
	if (!cmds || !cmds->cmd)
		return ;
	if (!ft_strncmp(cmds->cmd, "echo", 5) && ft_strlen(cmds->cmd) == 4)
		bt_echo(cmds);
	else if (!ft_strncmp(cmds->cmd, "cd", 3))
		bt_cd(envp, cmds->args, input);
	else if (!ft_strncmp(cmds->cmd, "exit", 5))
		bt_exit(input, cmds->args, cmds->arg_init);
	else if (!ft_strncmp(cmds->cmd, "pwd", 4) && ft_strlen(cmds->cmd) == 3)
		bt_pwd(*envp);
	else if (!ft_strncmp(cmds->cmd, "env", 4))
		bt_env(*envp);
	else if (!ft_strncmp(cmds->cmd, "export", 7))
		bt_export(envp, cmds->args, input);
	else if (!ft_strncmp(cmds->cmd, "unset", 6))
		bt_unset(envp, cmds->args, cmds->arg_init);
	else
		execve_threading(cmds, *envp);
	exit(0);
}

void	child_process(t_input *input, char ***envp, t_lstcmd *cmds)
{
	if (cmds->redi_init)
		exec_redirect(check_redirect(cmds->redis), cmds->redis, input);
	if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
		pipe_r(input);
	if (cmds->next)
		builtins(input, cmds, envp);
}

int	exec_process(t_input *input, char ***envp, t_lstcmd *cmds)
{
	if (cmds->pid == 0)
		child_process(input, envp, cmds);
	else
		if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
			pipe_w(input);
	return (0);
}

int	bt_no_fork(t_input *input, t_lstcmd *cmds, char ***envp)
{
	if (!cmds || !cmds->cmd)
		return (0);
	else if (!ft_strncmp(cmds->cmd, "cd", 3))
		return (bt_cd(envp, cmds->args, input));
	else if (!ft_strncmp(cmds->cmd, "exit", 5))
		return (bt_exit(input, cmds->args, cmds->arg_init));
	else if (!ft_strncmp(cmds->cmd, "export", 7) && cmds->arg_init)
		return (bt_export(envp, cmds->args, input));
	else if (!ft_strncmp(cmds->cmd, "unset", 6))
		return (bt_unset(envp, cmds->args, cmds->arg_init));
	return (0);
}

void	execution(t_input *input, char ***envp)
{
	t_lstcmd	*cmds;

	cmds = input->cmds;
	signal(SIGINT, handle_signals2);
	signal(SIGQUIT, handle_signals2);
	while (cmds && cmds->cmd)
	{
		if (!cmds->next)
			if (bt_no_fork(input, cmds, envp))
				break ;
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
	signal(SIGINT, handle_ctrl);
	signal(SIGQUIT, handle_ctrl);
	reset_std(input);
}
