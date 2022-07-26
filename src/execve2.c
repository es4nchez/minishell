/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:21:08 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/26 13:44:37 by yalthaus         ###   ########.fr       */
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
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**init_paths(char *cmd, int *i, char *path)
{
	char		*tmp;
	char		**paths;

	*i = -1;
	paths = ft_split(path, ':');
	while (paths && paths[++(*i)])
	{
		tmp = paths[*i];
		paths[*i] = ft_strjoin(paths[*i], cmd);
		free(tmp);
	}
	free(path);
	return (paths);
}

char	*cmd_exist(char *cmd, char *path)
{
	int			n;
	struct stat	buff;
	int			i;
	char		**paths;

	paths = init_paths(cmd, &i, path);
	n = i;
	i = -1;
	if (stat(cmd + 1, &buff) == 0)
		return (cmd);
	while (paths && paths[i + 1] && stat(paths[++i], &buff))
		;
	if (i == n - 1 || i == -1)
	{
		i = -1;
		while (paths && paths[++i])
			free(paths[i]);
		if (paths)
			free(paths);
		printf("mishellout: command not found: %s\n", cmd + 1);
		free(cmd);
		exit(127);
	}
	free(cmd);
	return (cmd_clean(paths, i));
}
