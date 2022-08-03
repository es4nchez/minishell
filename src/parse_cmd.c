#include "minishell.h"

void	cmd_arg(t_lstcmd *cmds, char **str, int type, char **envp)
{
	if (type == 0)
	{
		cmds->args = ft_pars_arg(str, envp);
		if (cmds->args)
			cmds->arg_init = 1;
		skip_space(str);
	}
	else if (type == 1)
	{
		cmds->redis = ft_pars_redi(str, envp);
		if (cmds->redis)
			cmds->redi_init = 1;
		skip_space(str);
	}
}