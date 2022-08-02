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

t_lstredi	*ft_pars_redi(char **str, char **envp)
{
	t_lstredi	*redis;
	t_lstredi	*tmp;
	char		*redi;
	char		*file;

	redis = ft_redi_new(NULL, NULL);
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
	tmp = redis->next;
	free(redis);
	redis = tmp;
	return (redis);
}

t_lstcmd	*init_cmd(void)
{
	t_lstcmd	*cmd;

	cmd = malloc(sizeof(t_lstcmd));
	if (!cmd)
		return (NULL);
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
	if (**str == '|')
		cmd->cmd = sep(str, **str, "|");
	else
	{
		cmd->cmd = sep(str, **str, "|>< ");
		skip_space(str);
		while (**str && **str != '|')
		{
			cmd->args = ft_pars_arg(str, envp);
			if (cmd->args)
				cmd->arg_init = 1;
			skip_space(str);
			cmd->redis = ft_pars_redi(str, envp);
			if (cmd->redis)
				cmd->redi_init = 1;
			skip_space(str);
		}
		string_clean(&(cmd->cmd), envp);
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
