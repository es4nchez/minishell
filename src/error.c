#include "minishell.h"

int ft_strerror(char *str, ...)
{
    va_list params;

    if (!str)
        return (1);
    va_start(params, str);
    while(str)
    {
        write(2, str, ft_strlen(str));
        str = va_arg(params, char *);
    }
    va_end(params);
    return (1);
}