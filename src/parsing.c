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
    if (**str && ft_isinset(c, "|<>"))
    {
        (*str) += 1;
        if (**str == c)
            (*str) += 1;
    }
    return (ft_substr(temp, 0, *str - temp));
}

char    *rm_quote(char *s)
{
    char    *temp;
    char    *ret;
    char    quote;
    int     i;

    i = 0;
    while (s[i] && s[i] != '\'' && s[i] != '"')
        i++;
    if (s[i] == '\0')
        return (s);
    quote = s[i];
    temp = ft_substr(s, 0, i);
    ret = ft_substr(s, i + 1, ft_strlen(s + i + 1));
    free(s);
    s = ft_strjoin(temp, ret);
    free(temp);
    free(ret);
    i = ft_strrchr(s, quote) - s;
    temp = ft_substr(s, 0, i);
    ret = ft_substr(s, i + 1, ft_strlen(s + i + 1));
    free(s);
    s = ft_strjoin(temp, ret);
    free(temp);
    free(ret);
    return (s);
}

void    string_clean(char **s, char **envp)
{
    char    *temp;
    int     i;

    i = -1;
    while ((*s)[++i])
    {
        if ((*s)[i] == '$')
        {
                temp = dol_parse(*s, envp);
                free(*s);
                *s = temp;
                return ;
        }
        if ((*s)[i] == '\"')
        {
            if (ft_strchr(&(*s)[i],'$'))
            {
                temp = dol_parse(*s, envp);
                free(*s);
                *s = temp;
            }
        }
    }
    *s = rm_quote(*s);
}

t_list    *ft_pars_arg(char **str, char **envp)
{
    t_list  *ret;
    t_list  *tmp;
    char    *s;

    skip_space(str);
    ret = ft_lstnew(NULL);
    while(!ft_isinset(**str, "|<> "))
    {
        s = sep(str, **str, "|<> ");
        printf("avant :%s\n", s);
        string_clean(&s, envp);
        printf("apres :%s\n", s);
        ft_lstadd_back(&ret, ft_lstnew(s));
        skip_space(str);
    }
    tmp = ret->next;
    free(ret);
    ret = tmp;
    return (ret);
}

t_lstredi    *ft_pars_redi(char **str, char **envp)
{
    t_lstredi   *redis;
    t_lstredi   *tmp;
    char        *redi;
    char        *file;

    redis = ft_Redi_new(NULL, NULL);
    skip_space(str);
    while(**str && ft_isinset(**str, "<>"))
    {
        redi = sep(str, **str, "<>");
        skip_space(str);
        file = sep(str, **str, "|<> ");
        string_clean(&file, envp);
        ft_redis_add_back(&redis, ft_Redi_new(redi, file));
        skip_space(str);
    }
    tmp = redis->next;
    free(redis);
    redis = tmp;
    return (redis);
}

t_lstcmd    *ft_pars_cmd(char **str, char **envp)
{
    t_lstcmd    *cmd;

	cmd = malloc(sizeof(t_lstcmd));
    cmd->redi_init = 0;
    cmd->arg_init = 0;
    skip_space(str);
    cmd->next = NULL;
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