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

void	bt_unset(char ***envp, t_list *args)
{
	int	i;

	while (args)
	{
		i = 0;
		while (ft_strncmp((*envp)[i], trim_equal(args->content, 0),
			ft_strlen(args->content)) != 0 && (*envp)[i])
			i++;
		i--;
		while ((*envp)[++i])
			(*envp)[i] = (*envp)[i + 1];
		args = args->next;
	}
	return;
}
