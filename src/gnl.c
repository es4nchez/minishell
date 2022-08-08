/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:06:04 by yalthaus          #+#    #+#             */
/*   Updated: 2021/11/13 14:51:39 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*end_line(char **buffer, char *tmp, int format)
{
	char	*ret;

	if (format < 0)
	{
		if (!**buffer)
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		ret = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (ret);
	}
	*buffer = ft_substr(*buffer, format + 1, ft_strlen(tmp));
	*(tmp + format) = '\0';
	ret = tmp;
	tmp = NULL;
	return (ret);
}

char	*read_line(int fd, char **buffer, char *curr_buffer, int buffer_size)
{
	char		*next_line;
	char		*tmp;
	int			nlpos;
	int			i;

	tmp = NULL;
	next_line = ft_strchr(*buffer, '\n');
	while (!next_line)
	{
		i = read(fd, curr_buffer, buffer_size);
		if (i <= 0)
			return (end_line(buffer, tmp, -1));
		curr_buffer[i] = '\0';
		tmp = ft_strjoin(*buffer, curr_buffer);
		free(*buffer);
		*buffer = tmp;
		next_line = ft_strchr(*buffer, '\n');
	}
	nlpos = 0;
	tmp = *buffer;
	while (tmp[nlpos] != '\n')
		nlpos++;
	return (end_line(buffer, tmp, nlpos));
}

char	*get_next_line(int fd)
{
	int			buffer_size;
	char		*ret;
	static char	*buffer[4096];
	char		*curr_buffer;

	buffer_size = 4096;
	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	curr_buffer = (char *)malloc((buffer_size + 1) * sizeof(char));
	if (!curr_buffer)
		return (NULL);
	ret = read_line(fd, buffer + fd, curr_buffer, buffer_size);
	free(curr_buffer);
	return (ret);
}
