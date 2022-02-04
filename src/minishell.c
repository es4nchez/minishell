/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:17 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/24 13:45:20 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	int		i;

	(void)argv;
	(void)argc;
	i = 0;
/*
	printf("\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("\n");
*/
	signal(SIGINT, handle_ctrl);
	while (1)
	{
		input = take_input();
		add_history(input);
		if (ft_strncmp(input, "", 1) == 0)
			continue ;
		else
			handle_input(input, envp);
	}
	return (0);
}
