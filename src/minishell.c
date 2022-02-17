/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:17 by esanchez          #+#    #+#             */
/*   Updated: 2022/02/04 16:20:41 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_termios(void)
{
	struct termios temp;

	tcgetattr(STDIN_FILENO, &temp);
	temp.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &temp);
}

int main(int argc, char **argv, char **envp)
{
	t_input		*input;
	//int		i;

	(void)argv;
	(void)argc;
	//i = 0;
/*
	printf("\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("\n");
*/

	signal(SIGQUIT, handle_ctrl);
	signal(SIGINT, handle_ctrl);
	ft_set_termios();
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
