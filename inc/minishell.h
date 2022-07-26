/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:26 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 15:15:32 by yalthaus         ###   ########.fr       */
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

typedef struct s_lstredi
{
    char                *redi;
    struct s_lstredi    *next;
    char                *file;
}               t_lstredi;

typedef struct s_lstcmd
{
    char                *cmd;
    struct s_lstcmd     *next;
    t_list              *args;
    t_lstredi           *redis;
    pid_t               pid;
    int                 redi_init;
    int                 arg_init;
}               t_lstcmd;

typedef struct s_input
{
	int				lstlen;
    char            *lineread;
    int             fd_io[2];
    int             pipe_fd[2];
    int             exit;
	t_lstcmd		*cmds;
}				t_input;

int g_retcmd;

/*
typedef struct s_stat {
    dev_t     st_dev;      ID of device containing file
    ino_t     st_ino;      inode number
    mode_t    st_mode;     protection
    nlink_t   st_nlink;    number of hard links
    uid_t     st_uid;      user ID of owner
    gid_t     st_gid;      group ID of owner
    dev_t     st_rdev;     device ID (if special file)
    off_t     st_size;     total size, in bytes
    blksize_t st_blksize;  blocksize for file system I/O
    blkcnt_t  st_blocks;   number of 512B blocks allocated
    time_t    st_atime;    time of last access
    time_t    st_mtime;    time of last modification
    time_t    st_ctime;    time of last status change
}	t_stat;
*/
typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
void    ft_process(t_input *input, char *str, char **envp);
char	*dir_name(void);
char	*take_input(void);
void	execution(t_input *input, char **envp);
void	handle_ctrl(int sig_nb);
void	execve_threading(t_lstcmd *cmd, char **envp);
void	print_env(char **envp);
void	export_env(char ***envp, char *input);
void	unset_env(char ***envp, char *input);
void    free_input(t_input *input);
void    bt_exit(t_input *input);
void    bt_env(char **envp);
void	bt_cd(char **envp, char *arg);
void    bt_input(t_input *input);
void    bt_echo(t_lstcmd *cmds);
void	bt_pwd(char **envp);
void	bt_export(char **envp, char *arg);
void	bt_unset(char **envp, char *arg);
char    *dol_parse(char *str, char **envp);
void	ft_cmdadd_back(t_lstcmd **cmds, t_lstcmd *new);
t_lstcmd	*ft_cmdnew(char *cmd, t_list *args);
void	ft_cmdclear(t_lstcmd **lst, void (*del)(void *));
t_lstredi    *ft_redi_new(char *redi, char *file);
void	ft_redis_clear(t_lstredi **lst, void (*del)(void *));
void	ft_redis_add_back(t_lstredi **redis, t_lstredi *new);
char    *get_env(char *str, char **envp);
int fd_process(int redi, t_lstredi *redis, int out);
int check_redirect(t_lstredi *redis);
char	*get_next_line(int fd);
int pipe_process(t_lstcmd *cmds);
void    pipe_w(t_input *input);
void    pipe_r(t_input *input);
void	reset_fds(t_input *input);
void	close_fds(t_input *input);
void	reset_std(t_input *input);
void	ft_close(int fd);
int	exec_redirect(int redi, t_lstredi *redis, t_input *input);
int len_equal(char *str);
char	*cmd_exist(char *cmd, char *path);
char	**init_paths(char *cmd, int *i, char *path);
char	*cmd_clean(char **paths, int i);
void	clear_tab(char **tab);
void	string_clean(char **s, char **envp);
char	*sep(char **str, char c, char *set);

#endif
