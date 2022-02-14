/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 08:43:05 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/21 18:00:48 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c);
static int	ft_size_words(char *s, char c);
static void	*ft_free(char **array, int i);

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (s[i] == c || s[0] == '\0')
		words--;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			words++;
		i++;
	}
	return (words + 1);
}

static int	ft_size_words(char *s, char c)
{
	int	size;

	size = 0;
	while (*s && *s != c)
	{
		size++;
		s++;
	}
	return (size);
}

static void	*ft_free(char **array, int i)
{
	while (i-- > 0)
		free(array[i]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**array;
	int		nword;

	if (!s)
		return (NULL);
	i = 0;
	nword = ft_count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!array)
		return (NULL);
	while (i < nword)
	{
		while (*s == c && *s)
			s++;
		array[i] = ft_substr(s, 0, ft_size_words((char *)s, c));
		if (array[i] == NULL)
			return (ft_free(array, i));
		s = s + ft_size_words((char *)s, c);
		i++;
	}
	array[i] = NULL;
	return (array);
}
