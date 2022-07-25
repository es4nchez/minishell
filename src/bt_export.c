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

void	bt_export(char ***envp, t_input *input)
{
	int		i;

	i = 0;
	if (ft_strlen(input->lineread) == 6)
		sort_env(*envp);
	else if (!export_errors(input->cmds->args->content))
		exit(printf("mishellout: export: '%s': not a valid identifier\n",
				input->cmds->args->content));
	else
	{
		while (input->cmds->args)
		{
			set_env(envp, trim_equal(input->cmds->args->content, 0),
				trim_equal(input->cmds->args->content, 1));
			input->cmds->args = input->cmds->args->next;
		}
	}
	return ;
}
