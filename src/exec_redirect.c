/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:29:45 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 12:51:40 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirect(int redi, t_lstredi *redis, t_input *input)
{
	while (redi > 0 && redi < 5 && redis)
	{
		if (redi > 0)
		{
			if (fd_process(redi, redis, input->fd_io[0]))
			{
				ft_strerror("mishellout: ", redis->file, ": no such file or directory\n");
				exit(2);
			}
		}
		redis = redis->next;
		redi = check_redirect(redis);
	}
	return (0);
}
