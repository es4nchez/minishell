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
	char	*var;

	if (!args_init)
		return (ft_strerror("unset: not enough arguments\n"));
	while (args)
	{
		var = trim_equal(args->content, 0);
		set_env(envp, var, NULL);
		if (var)
			free(var);
		args = args->next;
	}
	return (1);
}
