#include "minishell.h"

char    *concat_strvar(char *str, char *var, int loc)
{
    int     len;
    int     i;
    int     j;
    int     end;
    char    *res;

    i = 1;
    j = 0;
    while (ft_isalnum(str[loc + i]) || str[loc + i] == '_')
        i++;
    end = i;
    len = ft_strlen(str) + ft_strlen(var) - i;
    i = 0;
    res = (char *)ft_calloc(len + 1, sizeof(char));
    while (i < loc)
        res[i++] = str[j++];
    j = 0;
    while (var[j])
        res[i++] = var[j++];
    j = 0;
    while (str[loc + end + j])
        res[i++] = str[loc + end + j++];
    return (res);
}

char    *get_var(char *str)
{
    int     i;

    i = 0;
    str++;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    if (i)
        return (ft_substr(str, 0, i));
    return (NULL);
}
int len_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=' && str[i] != '\0')
        i++;
    return (i);
}
char    *get_env(char *str, char **envp)
{
    char    *rep;
    int     i;
    char    *temp;
    char    *var;

    i = 0;
    var = get_var(str);
    while (!ft_strnstr(envp[i], var, len_equal(envp[i])))
        i++;
    if (var)
        free(var);
    temp = ft_strchr(envp[i], '=');
    i = 0;
    while (temp[i] != '\0')
        i++;
    rep = ft_substr(temp, 1, i);
    return (rep);
}

char    *dol_parse(char *str, char **envp)
{
    char    *temp;
    char    *var;
    char    *res;

    if (*str == '"')
    {
        str++;
        temp = ft_strchr(str, '$');
        var = get_env(temp, envp);
        res = concat_strvar(str - 1, var, temp - str + 1);
        if (var)
            free(var);
        return (res);
    }
    else
        return (get_env(str, envp));
}