/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 02:22:13 by yalthaus          #+#    #+#             */
/*   Updated: 2021/10/16 05:49:04 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_fill(int n, int len, char **str)
{
	while (n > 9)
	{
		(*str)[--len] = n % 10 + '0';
		n = n / 10;
	}
	(*str)[--len] = n % 10 + '0';
}

static int	ft_count_digit(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 0;
	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
		len++;
	}
	len += ft_count_digit(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	ft_fill(n, len, &str);
	if (sign == 1)
		str[0] = '-';
	return (str);
}
