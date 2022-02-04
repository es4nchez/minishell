/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:45:26 by esanchez          #+#    #+#             */
/*   Updated: 2022/02/04 15:39:16 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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
# include <sys/stat.h>
# include <time.h>
# include <termios.h>

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

char	*dir_name(void);
char	*take_input(void);
void	handle_input(char *input, char **envp);
void	handle_ctrl(int sig_nb);
void	execve_threading(char *cmd, char **argv, char **envp);
void	print_env(char **envp);
void	export_env(char ***envp, char *input);
void	unset_env(char ***envp, char *input);
#endif
