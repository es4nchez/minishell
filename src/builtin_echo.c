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

int	is_fulln(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == 0 && i > 1)
		return (1);
	return (0);
}

int	get_option(t_list **lst, char c)
{
	int	ret;
	int	i;

	ret = 0;
	i = 1;
	while (((char *)(*lst)->content)[i] && *(char *)(*lst)->content == '-')
	{
		if (((char *)(*lst)->content)[i] == c)
			ret = 1;
		else
			ret = 0;
		i++;
	}
	while (*lst && ret == 1 && is_fulln((char *)(*lst)->content))
		(*lst) = (*lst)->next;
	return (ret);
}

void	bt_echo_print(t_list *temp)
{
	while (temp && temp->content)
	{
		write(1, temp->content, ft_strlen(temp->content));
		if (temp && temp->next && ((char *)(temp->content))[0] != '\0'
			&& ((char *)(temp->next->content))[0] != '\0')
			write(1, " ", 1);
		temp = temp->next;
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
	nl = get_option(&temp, 'n');
	if (nl)
		bt_echo_print(temp);
	else
	{
		bt_echo_print(temp);
		write(1, "\n", 1);
	}
	exit(0);
}
