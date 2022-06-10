/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:47:27 by esanchez          #+#    #+#             */
/*   Updated: 2022/03/30 15:47:29 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_variable(char **envp, int arg_nb, char *env_arg, char *env_val)
{
	envp[arg_nb] = ft_substr(envp[arg_nb], 0, ft_strlen(env_arg) + 1);
	envp[arg_nb] = ft_strjoin(envp[arg_nb], env_val);
	return ;
}

void	bt_export(char **envp, char *arg)
{
	char	*env_arg;
	char	*env_val;
	int		i;

	(void)envp;
	i = 0;
	if (!ft_split(arg, ' ')[1])
		return ;
	env_arg = ft_split(ft_split(arg, ' ')[1], '=')[0];
	env_val = ft_split(ft_split(arg, ' ')[1], '=')[1];
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], env_arg, ft_strlen(env_arg)) == 0)
		{
			change_variable(envp, i, env_arg, env_val);
			return ;
		}
		i++;
	}
	envp[i] = ft_strjoin(ft_strjoin(env_arg, "="), env_val);
	envp[i] = ft_strjoin(ft_strjoin(env_arg, "="), env_val);
	envp[i + 1] = NULL;
	return ;
}
