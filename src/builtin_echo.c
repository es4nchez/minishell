#include "minishell.h"

int get_option(t_list *lst, char c)
{
    int ret;
    int i;

    ret = 0;
    while (lst && lst->content)
    {
        if (*(char *)lst->content == '-')
        {
            i = 0;
            while (((char *)lst->content)[i])
            {
                i++;
                if (((char *)lst->content)[i] == c)
                {
                    ret = 1;
                    break ;
                }
                else
                    return (0); //TO DO strerror
            }
            
        }
        lst = lst->next;
    }
    return (ret);    
}

void    bt_echo_print(t_list *temp)
{
    while (temp && temp->content && *(char *)temp->content == '-')
    {
        temp = temp->next;
    }
    while (temp && temp->content)
    {
        write(1, temp->content, ft_strlen(temp->content));
        temp = temp->next;
        if (temp)
            write(1, " ", 1);
    }
}

void    bt_echo(t_lstcmd *cmds)
{
    t_list  *temp;
    int     nl;

    if (!cmds->arg_init)
        exit(1);
    temp = cmds->args;
    nl = get_option(temp, 'n');
    if (!temp)
    {
        write(1, "\n", 1);
        return ;
    }
    if (nl)
        bt_echo_print(temp);
    else
    {
        bt_echo_print(temp);
        write(1, "\n", 1);
    }
}