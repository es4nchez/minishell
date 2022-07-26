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
	if (!input)
		return (NULL);
	while (input[i] != '=' && input[i])
	{
		i++;
	}
	if (!part)
		return (ft_substr(input, 0, i));
	if (!input[i])
		return (ft_calloc(1, 1));
	return (ft_substr(input, i + 1, ft_strlen(input)));
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
	(*envp)[n] = NULL;
	*envp = ft_realloc(*envp, (len + 2) * sizeof(char *));
	if (!envp)
		return (1);
	i = -1;
	while ((*envp)[n])
	{
		(*envp)[n] = (*envp)[n];
		n++;
	}
	(*envp)[n] = tmp;
	return (0);
}

int	set_env(char ***envp, char *var, char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!envp || !var)
		return (1);
	while ((*envp)[i] && ft_strncmp((*envp)[i], var,
		len_equal((*envp)[i])) != 0)
		i++;
	if (content == NULL)
		return (rm_env(envp, i));
	if ((*envp)[i] == NULL)
		*envp = ft_realloc(*envp, (++i + 1) * sizeof(char *));
	if (content[0] == '\0')
		tmp = ft_strdup(var);
	else
		tmp = ft_strjoin(var, "=");
	free(var);
	var = ft_strjoin(tmp, content);
	free(tmp);
	free(content);
	if ((*envp)[i - 1])
		free((*envp)[i - 1]);
	(*envp)[i - 1] = var;
	return (0);
}

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
