/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:45:03 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/18 17:21:42 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	size_t	j;
	char	k;

	i = 0;
	j = 0;
	k = 0;
	while (i <= ft_strlen(str))
	{
		if (str[i] == (char)c)
		{
			j = i;
			k = 1;
		}
		i++;
	}
	if (k != 0)
		return ((char *)&str[j]);
	else
		return (NULL);
}
