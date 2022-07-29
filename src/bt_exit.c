/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:56:24 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/25 18:56:39 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(t_input *input, int ret)
{
	write(1, "exit\n", 5);
	free_input(input, ret);
}

int	bt_exit(t_input *input, t_list *args, int arg_init)
{
	int	n;
	int	i;

	n = 0;
	i = -1;
	if (arg_init == 0)
		exit_process(input, 0);
	while (args->content && ((char *)args->content)[++i])
		if (!ft_isdigit(((char *)args->content)[i]))
		{
			ft_strerror("mishellout: exit: numeric argument required\n", NULL);
			exit_process(input, 255);
		}
	if (args->next)
	{
		g_retcmd = ft_strerror("mishellout: exit: too many argument\n", NULL);
		return (0);
	}
	n = ft_atoi((char *)args->content);
	if (n > 255)
		exit_process(input, 244);
	exit_process(input, n);
	return (1);
}
