/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:06:13 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/14 21:29:18 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen((char *)s1);
	s = (char *)malloc((len + 1) * sizeof(char));
	if (s == (void *)0)
		return ((void *)0);
	while (i < len)
	{
		*(s + i) = *(s1 + i);
		i++;
	}
	*(s + i) = '\0';
	return (s);
}
