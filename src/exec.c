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

void	builtins(t_input *input, char **envp)
{
	// char	**cmd;
	// char	*final_cmd;

	// t_lstcmd	*lst;

	// (void)envp;
	// lst = input->cmds->next;
	// while (lst)
	// {
	// 	printf("CMD:\t%s\n", lst->cmd);
	// 	while (lst->args)
	// 	{
	// 		printf("ARG:\t\t%s\n", (char *)lst->args->content);
	// 		lst->args = lst->args->next;
	// 	}
	// 	lst = lst->next;
	// }
	//printf("%p\n", input);

	if (!ft_strncmp(input->cmds->cmd, "echo", 4))
		bt_echo(input->cmds);
	// cmd = ft_split(input, ' ');
	// final_cmd = ft_strjoin("/bin/", cmd[0]);
	else if (ft_strncmp(input->cmds->cmd, "cd", 2) == 0)
	 	bt_cd(envp, ft_split(input->lineread, ' ')[1]);
	else if (ft_strncmp(input->cmds->cmd, "exit", 4) == 0)
		bt_exit(input);
	else if (ft_strncmp(input->cmds->cmd, "pwd", 3) == 0)
		bt_pwd(envp);
	// else if (ft_strncmp(input, "echo -n", 7) == 0)
	// 	printf("%s\e[7m%%\e[0m\n", ft_substr(input, 8, ft_strlen(input)));
	// else if (ft_strncmp(input, "echo", 4) == 0 )
	// 	bt_echo();
	else if (ft_strncmp(input->cmds->cmd, "env", 3) == 0)
		bt_env(envp);
	else if (ft_strncmp(input->cmds->cmd, "export", 6) == 0)
	 	bt_export(envp, input->lineread);
	else if (ft_strncmp(input->cmds->cmd, "unset", 5) == 0)
		bt_unset(envp, input->lineread);
//	 else
//	 	execve_threading(final_cmd, cmd, envp);
	return ;
}
