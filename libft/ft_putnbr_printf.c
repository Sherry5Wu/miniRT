/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:24:09 by arissane          #+#    #+#             */
/*   Updated: 2024/07/21 11:19:18 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nbr_str(long argval, char *str, int len)
{
	long	temp;

	str[len] = '\0';
	while (argval > 0)
	{
		len--;
		temp = argval % 10;
		str[len] = temp + 48;
		argval = argval / 10;
	}
}

int	ft_putnbr_printf(long argval, char c)
{
	int		len;
	char	*str;

	if (argval == 0)
		return (ft_putchar_printf('0'));
	if (argval == -2147483648)
		return (ft_putstr_printf("-2147483648"));
	len = ft_nbr_len_printf(argval, c);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (-1);
	if (argval < 0)
	{
		str[0] = '-';
		argval = -argval;
	}
	nbr_str(argval, str, len);
	len = ft_putstr_printf(str);
	free(str);
	return (len);
}
