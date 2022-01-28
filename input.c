/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 19:48:02 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/24 19:48:03 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*take_input()
{
	char	*input;

	input = NULL;
	input = readline("\e[36mmishellout-0.4.2$ \e[0m");
	return (input);
}
