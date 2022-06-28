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

t_list    *ft_pars_arg(char **str)
{
    t_list    *ret;

    skip_space(str);
    ret = ft_lstnew(NULL);
    while(!ft_isinset(**str, "|<> "))
    {
        ft_lstadd_back(&ret, ft_lstnew(sep(str, **str, "|<> ")));
        skip_space(str);
    }
    return (ret);
}

t_lstcmd    *ft_pars_cmd(char **str)
{
    t_lstcmd    *cmd;

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
        cmd->args = ft_pars_arg(str);
        cmd->args = cmd->args->next;
        return (cmd);
    }
    cmd->args = ft_lstnew(NULL);
    return (cmd);
}

void    ft_process(t_input *input, char *str, char **envp)
{
    char    *tmp;

    (void)envp;
    tmp = str;
    if (!str || !input)
        return ;
    input->lstlen = 0;
    input->cmds = ft_cmdnew(NULL, NULL);
    while (*str)
    {
        ft_cmdadd_back(&(input->cmds), ft_pars_cmd(&str));
        input->lstlen++;
    }
    input->cmds = input->cmds->next;
    free(tmp);
}