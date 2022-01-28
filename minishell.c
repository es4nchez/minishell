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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
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
	while (1)
	{
		input = take_input();
		handle_input(input, argv, envp);
	}
	return (0);
}
