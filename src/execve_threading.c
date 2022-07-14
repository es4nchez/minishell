/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:55:09 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/28 13:55:12 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_clean(char **paths, int i)
{
	char	*cmd;

	cmd = ft_strdup(paths[i]);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (cmd);
}

void	clear_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*cmd_exist(char *cmd, char *path)
{
	int		n;
	struct stat	buff;
	char	**paths;
	char	*tmp;
	int		i;

	i = -1;
	buff.st_mode = 0;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(tmp);
	}
	free(path);
	n = i;
	i = -1;
	if (stat(cmd + 1, &buff) == 0)
		return (cmd);
	while (paths[i + 1] && stat(paths[++i], &buff));
	if (i == n - 1)
	{
		printf("mishellout: command not found: %s\n", cmd + 1);
		free(cmd);
		return (NULL);
	}
	return (cmd_clean(paths, i));
}

char	**execve_arg(t_lstcmd *cmd, char **envp)
{
	int		i;
	t_list	*arg;
	char	**ret;

	i = 1;
	arg = cmd->args;
	while(cmd->arg_init && arg)
	{
		i++;
		arg = arg->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	ret[0] = cmd_exist(ft_strjoin("/", cmd->cmd), get_env("$PATH", envp));
	arg = cmd->args;
	i = 1;
	while(cmd->arg_init && arg)
	{
		ret[i++] = ft_strdup(arg->content);
		arg = arg->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	execve_threading(t_lstcmd *cmd, char **envp)
{
	// pid_t	pid;
	// int		status;
	char	**argv;

	argv = execve_arg(cmd, envp);
	if (argv == NULL || argv[0] == NULL)
	{
		clear_tab(argv);
		return ;
	}
	// pid = fork();
	// if (pid == -1)
	// {
	// 	printf("Forking Error\n");
	// 	clear_tab(argv);
	// 	return ;
	// }
	// else if (pid == 0)
	// {
	execve(argv[0], argv, envp);
	clear_tab(argv);
	return ;
	// }
	// else
	// 	wait(&status);
	// clear_tab(argv);
	// return ;
}
