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
    {
        if (copen != '\'' && **str == '\'')
            get_quote(str, '\'');
        (*str)++;
    }
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

void    ft_process(t_input *input, char *str)
{
    int     i;

    i = 0;
    input->lst = ft_lstnew(NULL);
    while (*str)
    {
        ft_lstadd_front(&(input->lst), ft_lstnew(ft_proc(&str)));
        input->lstlen++;
    }
}