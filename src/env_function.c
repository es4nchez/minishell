/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:21:23 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/28 16:21:25 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_equal(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '=' && input[i])
	{
		i++;
	}
	return (ft_substr(input, 0, i));
}

void	unset_env(char ***envp, char *input)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[0][i], trim_equal(input), ft_strlen(input)) != 0 && envp[0][i])
	{
		i++;
	}
	while (envp[0][i])
	{
		envp[0][i] = envp[0][i + 1];
		i++;
	}
	envp[0][i] = NULL;
	return ;
}

void	export_env(char ***envp, char *input)
{
	int	i;

	i = 0;
	while (envp[0][i])
		i++;
	envp[0][i] = input;
	envp[0][i + 1] = NULL;
	return ;
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("\e[33m%s\e[0m\n", envp[i]);
		i++;
	}
	return ;
}
