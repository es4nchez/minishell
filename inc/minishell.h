/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:24:12 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/26 13:35:43 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <time.h>
# include <termios.h>
#include <stdarg.h>

typedef struct s_lstredi
{
	char				*redi;
	struct s_lstredi	*next;
	char				*file;
}						t_lstredi;

typedef struct s_lstcmd
{
	char			*cmd;
	struct s_lstcmd	*next;
	t_list			*args;
	t_lstredi		*redis;
	pid_t			pid;
	int				redi_init;
	int				arg_init;
}					t_lstcmd;

typedef struct s_input
{
	int			lstlen;
	char		*lineread;
	int			fd_io[2];
	int			pipe_fd[2];
	int			exit;
	t_lstcmd	*cmds;
}				t_input;

int	g_retcmd;

typedef void	*(t_sighandler)(int);
void			ft_process(t_input *input, char *str, char **envp);
char			*dir_name(void);
char			*take_input(void);
void			execution(t_input *input, char ***envp);
void			handle_ctrl(int sig_nb);
void			handle_signals2(int sig_nb);
void			execve_threading(t_lstcmd *cmd, char **envp);
void			print_env(char **envp);
void			export_env(char ***envp, char *input);
void			unset_env(char ***envp, char *input);
void			free_input(t_input *input, int ret);
int				bt_exit(t_input *input, t_list *args, int arg_init);
void			bt_env(char **envp);
void			bt_env_sorted(char **envp);
int				bt_cd(char ***envp, t_list *args, t_input *input);
void			bt_input(t_input *input);
void			bt_echo(t_lstcmd *cmds);
void			bt_pwd(char **envp);
int				bt_export(char ***envp, t_list *args, t_input *input);
int				bt_unset(char ***envp, t_list *args, int arg_init);
char			*trim_equal(char *input, int part);
char			*dol_parse(char *str, char **envp);
void			ft_cmdadd_back(t_lstcmd **cmds, t_lstcmd *new);
t_lstcmd		*ft_cmdnew(char *cmd, t_list *args);
void			ft_cmdclear(t_lstcmd **lst, void (*del)(void *));
t_lstredi		*ft_redi_new(char *redi, char *file);
void			ft_redis_clear(t_lstredi **lst, void (*del)(void *));
void			ft_redis_add_back(t_lstredi **redis, t_lstredi *new);
char			*get_env(char *str, char **envp);
int				rm_env(char ***envp, int n);
int				fd_process(int redi, t_lstredi *redis, int out);
int				check_redirect(t_lstredi *redis);
char			*get_next_line(int fd);
int				pipe_process(t_lstcmd *cmds);
void			pipe_w(t_input *input);
void			pipe_r(t_input *input);
void			reset_fds(t_input *input);
void			close_fds(t_input *input);
void			reset_std(t_input *input);
void			ft_close(int fd);
int				exec_redirect(int redi, t_lstredi *redis, t_input *input);
int				len_equal(char *str);
char			*cmd_exist(char *cmd, char *path);
char			**init_paths(char *cmd, int *i, char *path);
char			*cmd_clean(char **paths, int i);
void			clear_tab(char **tab);
void			string_clean(char **s, char **envp);
char			*sep(char **str, char c, char *set);
int				len_equal(char *str);
int				set_env(char ***envp, char *var, char *content);
void			print_sorted_env(char **envp);
void			sort_env(char **envp);
char			**env_dup(char **envp);
int				env_size(char **envp);
int				init_signal(int n);
void			*ft_free(void *ptr);
int				ft_strerror(char *str, ...);

#endif
