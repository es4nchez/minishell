/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:17 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 14:46:43 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_termios(void)
{
	struct termios	temp;

	tcgetattr(STDIN_FILENO, &temp);
	temp.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &temp);
}

static void	init_input(t_input **input)
{
	*input = (t_input *)malloc(sizeof(t_input));
	(*input)->lstlen = 0;
	(*input)->fd_io[1] = dup(STDOUT_FILENO);
	(*input)->fd_io[0] = dup(STDIN_FILENO);
	(*input)->exit = 0;
}

char	**env_dup(char **envp)
{
	char	**dup;
	int		i;

	i = 0;
	while (envp[i++])
		;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]);
	dup[i] = NULL;
	return (dup);
}

int	init_shell(t_input **input, char **argv, int argc)
{
	(void)argv;
	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_ctrl);
	ft_set_termios();
	init_input(input);
	if (!*input)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_input		*input;
	char		**env;

	env = env_dup(envp);
	if (init_shell(&input, argv, argc))
		return (1);
	while (1)
	{
		input->lineread = take_input();
		if (input->lineread == NULL)
			free_input(input, g_retcmd, env);
		ft_process(input, ft_strdup(input->lineread), env);
		if (input->cmds)
			add_history(input->lineread);
		if (ft_strncmp(input->lineread, "", 1) == 0)
			continue ;
		else
			execution(input, &env);
		if (input->lineread)
			ft_cmdclear(&(input->cmds), free);
		free(input->lineread);
	}
	free_envp(env);
	return (0);
}
