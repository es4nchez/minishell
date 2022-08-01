/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:55:52 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:03:56 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_option(t_list *lst, char c)
{
	int	ret;
	int	i;

	ret = 0;
	while (lst && lst->content)
	{
		if (*(char *)lst->content == '-')
		{
			i = 1;
			while (((char *)lst->content)[i])
			{
				if (((char *)lst->content)[i] == c)
					ret = 1;
				else
					return (0);
				i++;
			}	
		}
		lst = lst->next;
	}
	return (ret);
}

void	bt_echo_print(t_list *temp)
{
	while (temp && temp->content)
	{
		write(1, temp->content, ft_strlen(temp->content));
		temp = temp->next;
		if (temp)
			write(1, " ", 1);
	}
}

void	bt_echo(t_lstcmd *cmds)
{
	t_list	*temp;
	int		nl;

	if (!cmds->arg_init)
	{
		write(1, "\n", 1);
		exit(0);
	}
	temp = cmds->args;
	nl = get_option(temp, 'n');
	if (nl)
	{
		temp = temp->next;
		bt_echo_print(temp);
	}
	else
	{
		bt_echo_print(temp);
		write(1, "\n", 1);
	}
	exit(0);
}
