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

void	ft_waitpid(t_lstcmd *cmds)
{
	int	ret;

	while (cmds)
	{
		if (cmds->pid != 0)
			waitpid(cmds->pid, &ret, 0);
		cmds = cmds->next;
		if ( WIFEXITED(ret))
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

void	execution(t_input *input, char **envp)
{
	t_lstcmd	*cmds;
	t_lstredi	*redis;
	int			redi;
	int			nb_cmd;
	int			oldin;

	nb_cmd = 0;
	oldin = 0;
	cmds = input->cmds;
	while (cmds && cmds->cmd)
	{
		redi = -1;
		if (cmds->redi_init)
		{
			redis = cmds->redis;
			redi = check_redirect(redis);
		}
		if (cmds->next)
		{
			if (pipe(input->pipe_fd) == -1)
				return ;
		}
		cmds->pid = fork();
		if (cmds->pid == 0)
		{
			while (redi > 0 && redi < 5 && redis)
			{
				if (redi > 0)
					if (fd_process(redi, redis, input->fd_io[0]))
					{
						printf("mishellout: %s: no such file or directory\n", redis->file);
						exit(2);
					}
				redis = redis->next;
				redi = check_redirect(redis);
			}
   			ft_close(oldin);
			if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
        		pipe_r(input, &oldin);
			if (oldin != 0)
				ft_close(oldin);
			oldin = STDIN_FILENO;
			builtins(input, cmds, envp);
		}
		else
		{
    		oldin = STDIN_FILENO;
			if (cmds && !cmds->next && !ft_strncmp(cmds->cmd, "exit", 4))
				exit(0);
			else if (cmds && cmds->next && !ft_strncmp(cmds->cmd, "exit", 4)) 
				break ;
			if (cmds->next && !ft_strncmp(cmds->next->cmd, "|", 2))
				pipe_w(input, &oldin);
			nb_cmd++;
		}
		if (cmds->next && cmds->next->next)
			cmds = cmds->next->next;
		else
			cmds = NULL;
	}
	ft_waitpid(input->cmds);
	reset_std(input);
}
