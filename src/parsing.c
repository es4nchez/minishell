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

char    *pars(char **str, char c, pars_func *pt)
{
    char    *ret;

    while (**str)
    {
        if (**str == c)
            ret = (*pt)(next_word(*str));
        (*str)++; 
    }
    return (ret);
}