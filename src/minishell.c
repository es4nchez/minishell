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

static void	init_input(t_input **input)
{
	*input = (t_input *)malloc(sizeof(t_input));
	(*input)->lstlen = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_input		*input;
	//int		i;

	(void)argv;
	(void)envp;
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
	init_input(&input);
	if (!input)
		return (0);
	signal(SIGQUIT, handle_ctrl);
	signal(SIGINT, handle_ctrl);
	ft_set_termios();
	while (1)
	{
		ft_lstclear(&(input->lst), free);
		input->lineread = take_input();
		if (input->lineread == NULL)
		{
   			free_input(input);
			exit(0);
		}
		add_history(input->lineread);
		ft_process(input, ft_strdup(input->lineread));
		if (ft_strncmp(input->lineread, "", 1) == 0)
			continue ;
		else
			handle_input(input);
	}
	return (0);
}
