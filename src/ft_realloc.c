/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:15:39 by yalthaus          #+#    #+#             */
/*   Updated: 2022/01/04 09:51:49 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, int len)
{
	char	*ret;

	ret = malloc(len);
	if (ret == NULL)
		return (NULL);
	if (!ft_memcpy(ret, ptr, len - 8))
		return (NULL);
	*(ret + len - 8) = 0;
	free(ptr);
	return (ret);
}
