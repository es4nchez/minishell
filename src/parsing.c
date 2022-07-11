/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:17 by esanchez          #+#    #+#             */
/*   Updated: 2022/02/04 16:20:41 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char    *next_word(char *str)
// {
//     char    *s;
//     int     i;

//     i = 0;
//     s = ft_strdup(str);
//     while (*(s + i) != '\0' || *(s + i) != ' ')
//         i++;
//     *(s + i) = '\0';
//     return (s);
// }

// char    *pars(char *str, char c, pars_func *pt)
// {
//     char    *ret;

//     while (*str)
//     {
//         if (*str == c)
//             ret = (*pt)(next_word(str));
//         str++; 
//     }
//     return (ret);
// }

void    skip_space(char **str)
{
    while (**str && **str == ' ')
        (*str)++;
}

int	ft_isinset(char c, char *set)
{
	while (*set && c != '\0' && c != *set)
		set++;
	return (*set);
}

void    get_quote(char **str, char copen)
{
    (*str)++;
    while (**str != '\0' && **str != copen)
        (*str)++;
    if (**str == '\0')
        return ;                              //TODO : error quote non fermee
}

char    *sep(char **str, char c, char *set)
{
    char    *temp;

    temp = *str;
    while(**str && !ft_isinset(**str, set))
    {
        if (**str == '"' || **str == '\'')
            get_quote(str, **str);
        (*str)++;
    }
    if (ft_isinset(c, "|<>"))
            (*str)++;
    return (ft_substr(temp, 0, *str - temp));
}

char    *rm_quote(char *s)
{
    char    *temp;

    temp = ft_substr(s, 1, ft_strlen(s) - 2);
    free(s);
    return (temp);
}

t_list    *ft_pars_arg(char **str, char **envp)
{
    t_list  *ret;
    t_list  *tmp;
    char    *temp;
    char    *s;

    skip_space(str);
    ret = ft_lstnew(NULL);
    while(!ft_isinset(**str, "|<> "))
    {
        s = sep(str, **str, "|<> ");
        if (ft_strchr(s,'$') && s[0] != '\'')
        {
            temp = dol_parse(s, envp);
            free(s);
            s = temp;
        }
        if (s && (s[0] == '\'' || s[0] == '"'))
            s = rm_quote(s);
        ft_lstadd_back(&ret, ft_lstnew(s));
        skip_space(str);
    }
    tmp = ret->next;
    free(ret);
    ret = tmp;
    return (ret);
}

t_lstcmd    *ft_pars_cmd(char **str, char **envp)
{
    t_lstcmd    *cmd;
    char    *temp;

	cmd = malloc(sizeof(t_lstcmd));
    skip_space(str);
    cmd->next = NULL;
    if (**str == '|')
        cmd->cmd = sep(str, **str, "|");
    else if (**str == '<')
        cmd->cmd = sep(str, **str, "<");
    else if (**str == '>')
        cmd->cmd = sep(str, **str, ">");
    else
    {
        cmd->cmd = sep(str, **str, "|>< ");
        cmd->args = ft_pars_arg(str, envp);
        if (ft_strchr(cmd->cmd,'$') && cmd->cmd[0] != '\'')
        {
            temp = dol_parse(cmd->cmd, envp);
            free(cmd->cmd);
            cmd->cmd = temp;
        }
        return (cmd);
    }
    cmd->args = ft_lstnew(NULL);
    return (cmd);
}

void    ft_process(t_input *input, char *str, char **envp)
{
    char        *tmp;
    t_lstcmd    *temp;

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