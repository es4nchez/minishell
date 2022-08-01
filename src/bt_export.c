/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:47:27 by esanchez          #+#    #+#             */
/*   Updated: 2022/03/30 15:47:29 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_errors(char *input)
{
	if (!ft_isalpha(input[0]))
		return (0);
	return (1);
}

int	bt_export(char ***envp, t_list *args, t_input *input)
{
	if (ft_strlen(input->lineread) == 6)
		sort_env(*envp);
	else if (!export_errors(args->content))
		exit(ft_strerror("mishellout: export: ", (char *)args->content,
				": not a valid identifier\n"));
	else
	{
		while (args)
		{
			if (ft_strchr(args->content, '='))
				set_env(envp, trim_equal(args->content, 0),
					trim_equal(args->content, 1));
			else
				set_env(envp, trim_equal(args->content, 0),
					trim_equal(args->content, 1));
			args = args->next;
		}
	}
	return (1);
}
