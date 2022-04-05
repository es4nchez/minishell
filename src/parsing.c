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
    while (**str == ' ')
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
    while(!ft_isinset(**str, set))
    {
        if (**str == '"' || **str == '\'')
            get_quote(str, **str);
        (*str)++;
    }
    if (ft_isinset(c, "|<>"))
            (*str)++;
    return (ft_substr(temp, 0, *str - temp));
}

char    *ft_proc(char **str)
{
    char    *ret;

    skip_space(str);
    if (**str == '|')
        ret = sep(str, **str, "|");
    else if (**str == '<')
        ret = sep(str, **str, "<");
    else if (**str == '>')
        ret = sep(str, **str, ">");
    else
        ret = sep(str, **str, "|>< ");
    return (ret);
}

char    *get_env(char *var, char *envp)
{
    char    *rep;
    int     i;
    char    temp;

    i = 0;
    temp = ft_strnstr(envp, var, ft_strlen(envp));
    temp = ft_strchr(temp, '=');
    while (temp[i] != '\n')
        i++;
    rep = ft_substr(temp, 0, i);    

    return (rep);
}

char    *get_content_list(t_list *list)
{
    char    *rep;
    char    *dol;

    if (list->content != NULL)
    {
        rep = (char *)list->content;
        if (*rep == '"' || *rep == '\'')
        {
           
        }
    }
    else
        rep = NULL;
    return (rep);
}

char    *get_var(char *str)
{
    int i;
    char    *rep;

    i = 0;
    while (ft_isalnum(str[i]))
        i++;
    rep = ft_substr(str, 1, i);  
    return (rep);
}

char    *concat_strvar(char *str, char *var, int loc)
{
    int     len;
    char    *res;

    len = ft_strlen(str) + ft_strlen(var);
    res = (char *)malloc((len * sizeof(char)) + 1);
    
}

char    *quote_parse(char *str, char *envp)
{
    char    *dol;
    char    *temp;
    char    *var_res;
    char    *res;

    str++;
    if (*str == '"')
    {
        temp = ft_strchr(str, '$');
        if (temp != NULL)
        {
            dol = get_var(dol);
            var_res = get_env(dol, envp);
            if (dol)
                free(dol);
            res = concat_strvar(str, var_res, temp - str);
        }
    }


}

void    ft_process(t_input *input, char *str)
{
    char    *tmp;

    tmp = str;
    if (!str || !input)
        return ;
    input->lstlen = 0;
    while (*str)
    {
        ft_lstadd_back(&(input->lst), ft_lstnew(ft_proc(&str)));
        input->lstlen++;
    }
    free(tmp);
}