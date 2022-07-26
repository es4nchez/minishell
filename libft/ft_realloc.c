/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:15:39 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:29:41 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int len)
{
	char	*ret;

	ret = ft_calloc(len, sizeof(*ptr));
	if (ret == NULL)
		return (NULL);
	if (!ft_memcpy(ret, ptr, len - 8))
		return (NULL);
	*(ret + len - 8) = 0;
	free(ptr);
	return (ret);
}
