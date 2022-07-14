#include "minishell.h"

t_lstcmd	*ft_cmdnew(char *cmd, t_list *args)
{
	t_lstcmd	*element;

	element = malloc(sizeof(t_lstcmd));
	if (element == NULL)
		return (NULL);
	element->cmd = cmd;
	element->next = NULL;
    element->args = args;
	return (element);
}

t_lstcmd	*ft_cmdlast(t_lstcmd *cmds)
{
	if (!cmds)
		return (NULL);
	while (cmds->next != NULL)
		cmds = cmds->next;
	return (cmds);
}

void	ft_cmddelone(t_lstcmd *lst, void (*del)(void *))
{
	if (!lst || !(del))
		return ;
	(del)(lst->cmd);
	free(lst);
}

void	ft_cmdclear(t_lstcmd **lst, void (*del)(void *))
{
	t_lstcmd	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			if ((*lst)->arg_init)
			{
            	ft_lstclear(&((*lst)->args), free);
            	free((*lst)->args);
			}
			if ((*lst)->redi_init)
				ft_redis_clear(&((*lst)->redis), free);
			ft_cmddelone(*lst, del);
			(*lst) = tmp;
		}
	}
}

void	ft_cmdadd_back(t_lstcmd **cmds, t_lstcmd *new)
{
	t_lstcmd	*tmp;

	if (!cmds || !new)
		return ;
	if (*cmds)
	{
		tmp = ft_cmdlast(*cmds);
		tmp->next = new;
	}
	else
		*cmds = new;
}
