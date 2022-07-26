/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:18:10 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/26 13:43:23 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_unset(char ***envp, t_list *args, int args_init)
{
	int	i;

	if (!args_init)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	while (args)
	{
		i = 0;
		while ((*envp)[i] && ft_strncmp((*envp)[i],
				trim_equal(args->content, 0), ft_strlen(args->content)) != 0)
			i++;
		i--;
		while ((*envp)[++i])
			(*envp)[i] = (*envp)[i + 1];
		args = args->next;
	}
	return (1);
}
