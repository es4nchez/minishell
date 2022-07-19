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
    while (var && var[j])
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
    while (str && str[i] != '=' && str[i] != '\0')
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
    if (!var)
        return (NULL);
    while (envp[i] && (ft_strncmp(envp[i], var, len_equal(envp[i])) != 0 
        || ft_strncmp(envp[i], var, ft_strlen(var)) != 0))
        i++;
    if (envp[i] == NULL)
        return (NULL);
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

    temp = ft_strchr(str, '$');
    res = str;
    while (temp)
    {
        var = get_env(temp, envp);
        res = concat_strvar(res, var, temp - res);
        temp = ft_strchr(res, '$');
        if (var)
            free(var);
    }
    return (res);
}