/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:26:53 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:37:59 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

void	free_input(t_input *input, int ret, char **envp)
{
	if (input->lineread)
		ft_cmdclear(&(input->cmds), free);
	free(input->lineread);
	free(input);
	free_envp(envp);
	exit(ret);
}
