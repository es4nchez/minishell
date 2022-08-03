/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:53:54 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 15:18:41 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_pars_arg(char **str, char **envp)
{
	t_list	*ret;
	t_list	*tmp;
	char	*s;

	skip_space(str);
	ret = ft_lstnew(NULL);
	while (!ft_isinset(**str, "|<> "))
	{
		s = sep(str, **str, "|<> ");
		string_clean(&s, envp);
		ft_lstadd_back(&ret, ft_lstnew(s));
		skip_space(str);
	}
	tmp = ret->next;
	free(ret);
	ret = tmp;
	return (ret);
}

t_lstredi	*ft_pars_redi(char **str, char **envp, t_lstredi *old_redis)
{
	t_lstredi	*redis;
	char		*redi;
	char		*file;

	if (old_redis != NULL)
		redis = old_redis;
	skip_space(str);
	while (**str && ft_isinset(**str, "<>"))
	{
		redi = sep(str, **str, "<>");
		skip_space(str);
		file = sep(str, **str, "|<> ");
		string_clean(&file, envp);
		ft_redis_add_back(&redis, ft_redi_new(redi, file));
		skip_space(str);
	}
	return (redis);
}

t_lstcmd	*init_cmd(void)
{
	t_lstcmd	*cmd;

	cmd = malloc(sizeof(t_lstcmd));
	if (!cmd)
		return (NULL);
	cmd->redis = ft_redi_new(NULL, NULL);
	cmd->args = NULL;
	cmd->redi_init = 0;
	cmd->arg_init = 0;
	cmd->next = NULL;
	return (cmd);
}

t_lstcmd	*ft_pars_cmd(char **str, char **envp)
{
	t_lstcmd	*cmd;

	skip_space(str);
	if (**str == '\0')
		return (NULL);
	cmd = init_cmd();
	cmd_arg(cmd, str, 1, envp);
	if (**str == '|')
		cmd->cmd = sep(str, **str, "|");
	else
	{
		cmd->cmd = sep(str, **str, "|>< ");
		skip_space(str);
		while (**str && **str != '|')
		{
			cmd_arg(cmd, str, 0, envp);
			cmd_arg(cmd, str, 1, envp);
		}
		string_clean(&(cmd->cmd), envp);
		rm_null(&cmd->redis);
		return (cmd);
	}
	return (cmd);
}

void	ft_process(t_input *input, char *str, char **envp)
{
	char		*tmp;
	t_lstcmd	*temp;

	(void)envp;
	tmp = str;
	if (!str || !input)
		return ;
	input->lstlen = 0;
	input->cmds = ft_cmdnew(NULL, NULL);
	while (*str)
	{
		ft_cmdadd_back(&(input->cmds), ft_pars_cmd(&str, envp));
		input->lstlen++;
	}
	temp = input->cmds->next;
	free(input->cmds);
	input->cmds = temp;
	free(tmp);
}
