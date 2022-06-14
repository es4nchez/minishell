/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:18:10 by esanchez          #+#    #+#             */
/*   Updated: 2022/03/31 14:18:12 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_unset(char **envp, char *arg)
{
	char	*env_arg;
	int		i;

	i = 0;
	if (!ft_split(arg, ' ')[1])
		return ;
	env_arg = ft_split(ft_split(arg, ' ')[1], '=')[0];
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], env_arg, ft_strlen(env_arg)) == 0)
		{
			envp[i] = envp[i + 1];
			return ;
		}
		i++;
	}
	return ;
}
