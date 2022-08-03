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
	set_env(envp, ft_strdup("PWD"), pwd);
}

void	cd_home(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "HOME=", 5) != 0)
		i++;
	if (i == env_size(*envp))
	{
		ft_strerror("mishellout: cd: HOME not set\n", NULL);
		return ;
	}
	set_env(envp, ft_strdup("OLDPWD"), dir_name());
	chdir((*envp)[i] + 5);
	set_env(envp, ft_strdup("PWD"), dir_name());
	return ;
}

int	bt_cd(char ***envp, t_list *args, t_lstcmd *cmds)
{
	if (!cmds->arg_init)
	{
		cd_home(envp);
		return (1);
	}
	if (chdir(args->content) == -1)
		ft_strerror("mishellout: cd: ", (char *)args->content,
			": No such file or directory\n", NULL);
	else
		change_pwd(envp, dir_name(), "tt");
	return (1);
}
