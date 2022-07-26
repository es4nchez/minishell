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

void	change_pwd(char ***envp, char *pwd, char *oldpwd)
{
	(void)oldpwd;
	set_env(envp, "PWD", pwd, 1);
}

void	cd_home(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "HOME=", 5) != 0)
		i++;
	if (i == env_size(*envp))
	{
		printf("mishellout: cd: HOME not set\n");
		return ;
	}
	set_env(envp, "OLDPWD", dir_name(), 1);
	chdir((*envp)[i] + 5);
	set_env(envp, "PWD", dir_name(), 1);
	return ;
}

int	bt_cd(char ***envp, t_list *args, t_input *input)
{
	int		i;

	i = 0;
	if (ft_strlen(input->lineread) == 2)
	{
		cd_home(envp);
		return (0);
	}
	if (chdir(args->content) == -1)
		printf("mishellout: cd: %s: No such file or directory\n",
			args->content);
	else
		change_pwd(envp, dir_name(), "tt");
	return (1);
}
