#include "minishell.h"

char    *next_word(char *str)
{
    char    *s;
    int     i;

    i = 0;
    s = ft_strdup(str);
    while (*(s + i) != '\0' || *(s + i) != ' ')
        i++;
    *(s + i) = '\0';
    return (s);
}

char    *pars(char *str, char c, pars_func *pt)
{
    char    *ret;

    while (*str)
    {
        if (*str == c)
            ret = (*pt)(next_word(str));
        str++; 
    }
    return (ret);
}

void    skip_space(char **str)
{
    while (**str == ' ')
        *str++;
}

char    *proc_dquote(char **str)
{
    char    *temp;

    temp = *str;
    (*str)++;
    while(**str != '\0' && **str != '"')
        (*str)++;
    return (ft_substr(temp, 0, *str - temp));
}

char    *proc_quote(char **str)
{
    char    *temp;

    temp = *str;
    (*str)++;
    while(**str != '\0' && **str != '\'')
        (*str)++;
    return (ft_substr(temp, 0, *str - temp));
}

char    *proc_doll(char **str)
{
    
}

char    *proc(char **str)
{
    char    *ret;
    skip_space(str);
    if (**str == '"')
        ret = proc_dquote(str);
    else if (**str == '\'')
        ret = proc_quote(str);
    else if (**str == '$')
        ret = proc_doll(str);
    else if (**str == '|')
        ret = proc_pipe(str);
    else if (**str == '<')
        ret = proc_chevg(str);
    else if (**str == '>')
        ret = proc_chevd(str);
    else
        ret = proc_cmd(str);
    return (ret);
}
char    *ft_process(char *str)
{
    char    **strs;
    int     i;

    i = 0;
    while (*str)
    {
        
        str++;
    }
}