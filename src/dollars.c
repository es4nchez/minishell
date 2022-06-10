/*#include "minishell.h"

char    *concat_strvar(char *str, char *var, int loc)
{
    int     len;
    int     i;
    int     j;
    int     end;
    char    *res;

    i = 0;
    j = 0;
    while (ft_isalnum(str[loc + i]) || str[loc + i] == '_')
        i++;
    end = i;
    i = 0;
    len = ft_strlen(str) + ft_strlen(var) - i;
    res = (char *)malloc((len * sizeof(char)) + 1);
    while (i < loc)
        res[i++] = str[j++];
    j = 0;
    while (var[j])
        res[i++] = var[j++];
    j = 0;
    while (str[loc + end + j])
        res[i++] = str[loc + end + j];
    return (res);
}

char    *get_var(char *str)
{
    int     i;
    char    *rep;

    i = 0;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    rep = ft_substr(str, 1, i);
    return (rep);
}

char    *get_env(char *str, char **envp)
{
    char    *rep;
    int     i;
    char    *temp;
    char    *var;

    i = 0;
    var = get_var(str);
    while (temp = ft_strnstr(envp[i], var, ft_strlen(envp[i++])))
    {
        ;
    }
    if (var)
        free(var);
    temp = ft_strchr(temp, '=');
    while (temp[i] != '\0')
        i++;
    rep = ft_substr(temp, 0, i);
    return (rep);
}

char    *dol_parse(char *str, char **envp)
{
    char    *temp;
    char    *var;
    char    *res;

    str++;
    if (*str == '"')
    {
        temp = ft_strchr(str, '$');
        var = get_env(temp, envp);
        res = concat_strvar(str, var, temp - str);
        if (var)
            free(var);
        free(str);
        return (res);
    }
    else
    {
        var = get_env(str, envp);
        free(str);
        return (var);
    }
}*/