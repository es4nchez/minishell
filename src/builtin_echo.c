#include "minishell.h"

int get_option(t_list *lst, char c)
{
    int ret;
    int i;

    ret = 0;
    while (lst)
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

void    bt_echo_print(t_list *temp, int n)
{
    int i;

    i = 0;
    while (temp && *(char *)temp->content == '-')
    {
        temp = temp->next;
        n--;
    }
    while (i < n - 1)
    {
        write(1, temp->content, ft_strlen(temp->content));
        temp = temp->next;
        if (temp)
            write(1, " ", 1);
        i++;
    }
}

void    bt_echo(t_input *input)
{
    t_list  *temp;
    int     nl;

    temp = input->lst->next;
    nl = get_option(temp, 'n');
    if (!temp)
    {
        write(1, "\n", 1);
        return ;
    }
    if (nl)
        bt_echo_print(temp, input->lstlen);
    else
    {
        bt_echo_print(temp, input->lstlen);
        write(1, "\n", 1);
    }
}