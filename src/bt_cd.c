/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:56:48 by esanchez          #+#    #+#             */
/*   Updated: 2022/03/25 14:56:51 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_cd(char **envp, char *arg)
{
	int	i;
	char	*error;

	i = 0;
	if (!arg)
	{
		while (ft_strncmp(envp[i], "HOME=", 5) != 0)
			i++;
		arg = ft_substr(envp[i], 5, 255);
		chdir(arg);
	}
	else if (chdir(arg) == -1)
	{
		error = ft_strjoin("cd: ", arg);
		perror(error);
	}
	return ;
}
