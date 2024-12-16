/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:27:03 by arissane          #+#    #+#             */
/*   Updated: 2024/07/21 11:18:59 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	hex_str(size_t argval, char c, char *str, int len)
{
	long	temp;

	str[len] = '\0';
	while (argval > 0)
	{
		len--;
		temp = argval % 16;
		if (temp < 10)
			str[len] = temp + 48;
		else if (c == 'x')
			str[len] = temp + 87;
		else if (c == 'X')
			str[len] = temp + 55;
		argval = argval / 16;
	}
}

int	ft_puthex_printf(size_t argval, char c)
{
	int		len;
	char	*str;

	if (argval == 0)
		return (ft_putchar_printf('0'));
	len = ft_nbr_len_printf(argval, c);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (-1);
	hex_str(argval, c, str, len);
	len = ft_putstr_printf(str);
	free(str);
	return (len);
}
