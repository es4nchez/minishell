/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:32:15 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:32:37 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstredi	*ft_redi_new(char *redi, char *file)
{
	t_lstredi	*element;

	element = malloc(sizeof(t_lstredi));
	if (element == NULL)
		return (NULL);
	element->redi = redi;
	element->next = NULL;
	element->file = file;
	return (element);
}

t_lstredi	*ft_redis_last(t_lstredi *redis)
{
	if (!redis)
		return (NULL);
	while (redis->next != NULL)
		redis = redis->next;
	return (redis);
}

void	ft_redis_delone(t_lstredi *lst, void (*del)(void *))
{
	if (!lst || !(del))
		return ;
	(del)(lst->redi);
	(del)(lst->file);
	free(lst);
}

void	ft_redis_clear(t_lstredi **lst, void (*del)(void *))
{
	t_lstredi	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_redis_delone(*lst, del);
			(*lst) = tmp;
		}
	}
}

void	ft_redis_add_back(t_lstredi **redis, t_lstredi *new)
{
	t_lstredi	*tmp;

	if (!redis || !new)
		return ;
	if (*redis)
	{
		tmp = ft_redis_last(*redis);
		tmp->next = new;
	}
	else
		*redis = new;
}
