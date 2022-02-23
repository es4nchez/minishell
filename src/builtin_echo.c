#include "minishell.h"

void    bt_echo_print(t_list *temp, int n)
{
    int i;

    i = 0;
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

    temp = input->lst->next;
    if (!temp)
    {
        write(1, "\n", 1);
        return ;
    }
    if (!ft_strncmp(temp->content, "-n", 2))
    {
        input->lstlen--;
        temp = temp->next;
        bt_echo_print(temp, input->lstlen);
    }
    else
    {
        bt_echo_print(temp, input->lstlen);
        write(1, "\n", 1);
    }
}