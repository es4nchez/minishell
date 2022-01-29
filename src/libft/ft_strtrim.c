/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:06:28 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/14 22:24:40 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char *set)
{
	while (*set && c != *set)
		set++;
	return (*set);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_isinset(*(s1 + i), (char *)set) && *(s1 + i))
		i++;
	while (ft_isinset(*(s1 + j - 1), (char *)set) && i != j)
		j--;
	return (ft_substr(s1, i, j - i));
}
