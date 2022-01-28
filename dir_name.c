/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:32:46 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/24 15:32:49 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dir_name()
{
	char	*dir_name;

	dir_name = NULL;
	dir_name = getcwd(dir_name, 0);
	return (dir_name);
}

