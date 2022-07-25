/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:44:48 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 03:04:24 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("\e[33m%s\e[0m\n", envp[i]);
		i++;
	}
}

int		env_size(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	print_sorted_var(char *var)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (var[i] != '=')
		printf("%c", var[i++]);
	printf("%c", var[i++]);
	printf("\"");
	while (var[i])
		printf("%c", var[i++]);
	printf("\"\n");

}

void	print_sorted_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			print_sorted_var(envp[i]);
	else
		printf("declare -x %s=\n", envp[i]);
		i++;
	}
	return ;
}

void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*tmp_str;
	char	**tmp_arr;

	i = 0;
	tmp_arr = env_dup(envp);
	while (i < env_size(tmp_arr) - 1)
	{
		j = 0;
		while (j < (env_size(tmp_arr) - i - 1))
		{
			if(ft_strncmp(tmp_arr[j], tmp_arr[j + 1], 150) > 0)
			{
				tmp_str = tmp_arr[j];
				tmp_arr[j] = tmp_arr[j + 1];
				tmp_arr[j + 1] = tmp_str;
			}
			j++;
		}
		i++;
	}
	print_sorted_env(tmp_arr);
	free(tmp_arr);
}
