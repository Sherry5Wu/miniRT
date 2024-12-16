/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:12:54 by arissane          #+#    #+#             */
/*   Updated: 2024/12/09 11:41:32 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int		len;
	long	i;

	len = 0;
	i = n;
	if (i < 0 || i == 0)
	{
		i = -i;
		len++;
	}
	while (i > 0)
	{
		len++;
		i = i / 10;
	}
	return (len);
}

static char	*addnb(char *str, int n, int len, int sign)
{
	if (n == -2147483648)
	{
		str[len] = '8';
		n = 214748364;
		len--;
	}
	if (len == 0)
		str[len] = n + 48;
	while (len >= 0)
	{
		if (sign < 0 && len == 0)
			str[len] = '-';
		else
			str[len] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	sign = 1;
	len = length(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	str[len] = '\0';
	len--;
	str = addnb(str, n, len, sign);
	return (str);
}
