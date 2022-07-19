/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 22:45:33 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/14 18:50:55 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	pos;
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	pos = 0;
	while (*(haystack + pos) && pos < len)
	{
		i = 0;
		while (*(needle + i) && *(haystack + pos + i) == *(needle + i)
			&& (pos + i) < len)
		{
			++i;
			if (!*(needle + i))
				return ((char *)(haystack + pos));
		}
		pos++;
	}
	return (NULL);
}
