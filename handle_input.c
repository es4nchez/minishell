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

void	handle_input(char *input, char **argv, char **envp)
{
	if (ft_strncmp(input, "cd ", 3) == 0)
		chdir(ft_substr(input, 3, ft_strlen(input)));
	if (ft_strncmp(input, "exit", 4) == 0)
		exit(0);
	if (ft_strncmp(input, "pwd", 3) == 0)
		printf("%s\n", dir_name());
	if (ft_strncmp(input, "echo -n", 4) == 0)
		printf("%s\n", ft_substr(input, 7, ft_strlen(input)));
	if (ft_strncmp(input, "ls", 2) == 0)
		execve_threading("/bin/ls", argv, envp);
	if (ft_strncmp(input, "env", 3) == 0)
		print_env(envp);
	return ;
}
