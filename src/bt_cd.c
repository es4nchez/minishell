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

void	bt_cd(char ***envp, t_input *input)
{
	int	i;

	i = 0;
	if (ft_strlen(input->lineread) == 2)
	{
		while ((*envp)[i] && ft_strncmp((*envp)[i], "HOME=", 5) != 0)
			i++;
		chdir((*envp)[i] + 5);
	}
	else if (chdir(input->cmds->args->content) == -1)
		printf("mishellout: cd: %s: No such file or directory\n",
			input->cmds->args->content);
	return ;
}
