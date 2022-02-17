#include "minishell.h"

void    bt_echo(t_input *input)
{
    int i;
    t_list  *temp;

    i = -1;
    temp = input->lst;
    while (++i < input->lstlen)
    {
        printf(temp);
        temp = temp->next;
    }
}