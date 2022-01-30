/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:32:46 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/29 12:17:40 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dir_name(void)
{
	char	*dir_name;

	dir_name = NULL;
	dir_name = getcwd(dir_name, 0);
	return (dir_name);
}
