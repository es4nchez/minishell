/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:53:22 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/24 19:53:24 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input(t_input *input)
{
// 	char	**cmd;
// 	char	*final_cmd;

	if (!ft_strncmp(input->lst->content, "echo", 4))
		bt_echo(input);
	// cmd = ft_split(input, ' ');
	// final_cmd = ft_strjoin("/bin/", cmd[0]);
	// if (ft_strncmp(input, "cd ", 3) == 0)
	// 	chdir(ft_substr(input, 3, ft_strlen(input)));
	// else if (ft_strncmp(input, "exit", 4) == 0)
	// 	exit(0);
	// else if (ft_strncmp(input, "pwd", 3) == 0)
	// 	printf("%s\n", dir_name());
	// else if (ft_strncmp(input, "echo -n", 7) == 0)
	// 	printf("%s\e[7m%%\e[0m\n", ft_substr(input, 8, ft_strlen(input)));
	// else if (ft_strncmp(input, "echo", 4) == 0 )
	// 	bt_echo();
	// else if (ft_strncmp(input, "env", 3) == 0)
	// 	print_env(envp);
	// else if (ft_strncmp(input, "export", 6) == 0)
	// 	export_env(&envp, cmd[1]);
	// else if (ft_strncmp(input, "unset", 5) == 0)
	// 	unset_env(&envp, cmd[1]);
	// else
	// 	execve_threading(final_cmd, cmd, envp);
	return ;
}
