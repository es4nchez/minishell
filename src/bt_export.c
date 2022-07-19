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

int	rm_env(char ***envp, int n)
{
	int	i;
	int	len;
	char	*tmp;

	i = 0;
	if ((*envp)[n] == NULL)
		return (1);
	while ((*envp)[i])
		i++;
	len = i;
	tmp  = ft_strdup((*envp)[len]);
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

int	set_env(char ***envp, char *var, char *content)
{
	int i;
	int	len;
	char	*tmp;

	i = 0;
	if (!envp || !var)
		return (1);
	while ((*envp)[i] && ft_strncmp((*envp)[i], var, len_equal((*envp)[i])) != 0)
		i++;
	if (!content)
		return (rm_env(envp, i));
	if ((*envp)[i] == NULL)
		envp = ft_realloc(*envp, ++i);
	tmp = ft_strjoin(var, "=");
	free(var);
	var = ft_strjoin(tmp, content);
	free(tmp);
	free(content);
	free((*envp)[i]);
	(*envp)[i] = var;
	return (0);
}

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
