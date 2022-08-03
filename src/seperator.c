/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:10:51 by yalthaus          #+#    #+#             */
/*   Updated: 2022/08/01 18:11:32 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_quote(char **str, char copen)
{
	(*str)++;
	while (**str != '\0' && **str != copen)
		(*str)++;
	if (**str == '\0')
		return ;
}

char	*sep(char **str, char c, char *set)
{
	char	*temp;

	temp = *str;
	while (**str && !ft_isinset(**str, set))
	{
		if (**str == '"' || **str == '\'')
		{
			get_quote(str, **str);
			if (**str == '\0')
			{
				ft_strerror("mishellout: quote not closed\n", NULL);
				return (NULL);
			}
		}
		(*str)++;
	}
	if (**str && ft_isinset(c, "|<>"))
	{
		(*str) += 1;
		if (**str == c)
			(*str) += 1;
	}
	return (ft_substr(temp, 0, *str - temp));
}

char	*rm_quote(char *s)
{
	char	*temp;
	char	*ret;
	char	quote;
	int		i;

	i = 0;
	while (s[i] && s[i] != '\'' && s[i] != '"')
		i++;
	if (s[i] == '\0')
		return (s);
	quote = s[i];
	temp = ft_substr(s, 0, i);
	ret = ft_substr(s, i + 1, ft_strlen(s + i + 1));
	free(s);
	s = ft_strjoin(temp, ret);
	free(temp);
	free(ret);
	i = ft_strrchr(s, quote) - s;
	temp = ft_substr(s, 0, i);
	ret = ft_substr(s, i + 1, ft_strlen(s + i + 1));
	free(s);
	s = ft_strjoin(temp, ret);
	free(temp);
	free(ret);
	return (s);
}

void	dol_swap(char **s, char **envp)
{
	char	*temp;

	temp = dol_parse(*s, envp);
	free(*s);
	*s = temp;
}

void	string_clean(char **s, char **envp)
{
	int		i;

	i = 0;
	if (!*s)
		return ;
	while ((*s)[i])
	{
		if (!ft_strrchr(&(*s)[i], '"') && (*s)[i] == '\'')
			while ((*s)[++i] != '\0' && (*s)[i] != '\'')
				;
		if ((*s)[i] == '$')
		{
			dol_swap(s, envp);
			*s = rm_quote(*s);
			return ;
		}
		if ((*s)[i] == '\"')
			if (ft_strchr(&(*s)[i], '$'))
				dol_swap(s, envp);
		++i;
	}
	*s = rm_quote(*s);
}
