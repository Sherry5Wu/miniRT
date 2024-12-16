/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:17:00 by arissane          #+#    #+#             */
/*   Updated: 2024/07/21 11:19:34 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ptr_len(size_t argval)
{
	int	len;

	len = 0;
	while (argval > 0)
	{
		argval = argval / 16;
		len++;
	}
	return (len);
}

static void	hex_str(size_t argval, char *str, int len)
{
	long	temp;

	str[len] = '\0';
	while (argval > 0)
	{
		len--;
		temp = argval % 16;
		if (temp < 10)
			str[len] = temp + 48;
		else
			str[len] = temp + 87;
		argval = argval / 16;
	}
}

int	ft_putptr_printf(size_t argval)
{
	int		len;
	char	*str;

	if (ft_putstr_printf("0x") == -1)
		return (-1);
	if (argval == 0)
	{
		if (ft_putchar_printf('0') == -1)
			return (-1);
		else
			return (3);
	}
	len = ptr_len(argval);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (-1);
	hex_str(argval, str, len);
	len = ft_putstr_printf(str);
	if (len != -1)
		len += 2;
	free(str);
	return (len);
}
