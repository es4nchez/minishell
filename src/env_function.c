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

char	*trim_equal(char *input, int part)
{
	int	i;

	i = 0;
	if (part && !ft_strchr(input, '='))
		return (NULL);
	while (input[i] != '=' && input[i])
	{
		i++;
	}
	if (!part)
		return (ft_substr(input, 0, i));
	return (ft_substr(input, i, ft_strlen(input)));
}

int	rm_env(char ***envp, int n)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if ((*envp)[n] == NULL)
		return (1);
	while ((*envp)[i])
		i++;
	len = i;
	tmp = ft_strdup((*envp)[len]);
	free((*envp)[i]);
	free((*envp)[n]);
	envp = ft_realloc(*envp, len - 1);
	if (!envp)
		return (1);
	i = -1;
	while ((*(*envp)[n]))
	{
		(*envp)[n] = (*envp)[n + 1];
		n++;
	}
	(*envp)[n] = tmp;
	return (0);
}

int	set_env(char ***envp, char *var, char *content, int eq)
{
	int	i;

	i = 0;
	if (!envp || !var || var[0] == '=')
		return (1);
	while ((*envp)[i] && ft_strncmp((*envp)[i], var, len_equal((*envp)[i]) - 1)
		!= 0)
		i++;
	if ((*envp)[i] == NULL)
		*envp = ft_realloc(*envp, (i + 1) * 9);
	if (eq)
	{
		var = ft_strjoin(var, content);
		free(content);
	}
	free((*envp)[i]);
	(*envp)[i] = var;
	return (0);
}
/*if ((*envp)[i] == NULL)
		envp = ft_realloc(*envp, ++i);
	tmp = ft_strjoin(var, "=");
	free(var);
	var = ft_strjoin(tmp, content);
	free(tmp);
	free(content);
	free((*envp)[i]);
	(*envp)[i] = var;
	return (0);
*/
void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') && envp[i + 1])
			printf("\e[33m%s\e[0m\n", envp[i]);
		i++;
	}
	return ;
}
