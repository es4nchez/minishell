/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:48:02 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/29 15:03:23 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_input(void)
{
	char	*input;

	input = NULL;
	input = readline("\e[36mmishellout-0.4.2$ \e[0m");
	return (input);
}
