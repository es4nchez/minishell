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
	free(cmd);
	n = i;
	i = -1;
	while (stat(paths[++i], &buff) != 0);
	if (i == n)
		return (NULL);
	return (cmd_clean(paths, i));
}

void	cmd_not_found(char *cmd)
{
	printf("mishellout: command not found: %s\n", cmd);
}

char	**execve_arg(t_lstcmd *cmd, char **envp)
{
	int		i;
	t_list	*arg;
	char	**ret;

	i = 1;
	arg = cmd->args;
	while(arg)
	{
		i++;
		arg = arg->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	ret[0] = cmd_exist(ft_strjoin("/", cmd->cmd), get_env("$PATH", envp));
	arg = cmd->args;
	i = 1;
	while(arg)
	{
		ret[i++] = ft_strdup(arg->content);
		arg = arg->next;
	}
	ret[i] = NULL;
	return (ret);
}

void	execve_threading(t_lstcmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	char	**argv;

	argv = execve_arg(cmd, envp);
	if (argv[0] == NULL)
	{
		cmd_not_found(argv[0]);
		clear_tab(argv);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Forking Error\n");
		clear_tab(argv);
		return ;
	}
	else if (pid == 0)
	{
		execve(argv[0], argv, envp);
		clear_tab(argv);
		return ;
	}
	else
		wait(&status);
	clear_tab(argv);
	return ;
}
