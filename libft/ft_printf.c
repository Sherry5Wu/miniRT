/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:47:38 by arissane          #+#    #+#             */
/*   Updated: 2024/07/21 11:18:19 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_type(char c, va_list arguments)
{
	void	*ptr;

	if (c == 'c')
		return (ft_putchar_printf(va_arg(arguments, int)));
	if (c == 's')
		return (ft_putstr_printf(va_arg(arguments, char *)));
	if (c == 'p')
	{
		ptr = va_arg(arguments, void *);
		if (ptr == NULL)
			return (ft_putstr_printf("0x0"));
		else
			return (ft_putptr_printf((size_t)ptr));
	}
	if (c == 'd' || c == 'i')
		return (ft_putnbr_printf(va_arg(arguments, int), c));
	if (c == 'u')
		return (ft_putnbr_printf(va_arg(arguments, unsigned int), c));
	if (c == 'x' || c == 'X')
		return (ft_puthex_printf(va_arg(arguments, unsigned int), c));
	if (c == '%')
		return (ft_putchar_printf(c));
	return (ft_putchar_printf('%') + ft_putchar_printf(c));
}

static int	check_input(const char *str, va_list arguments, int i, int len)
{
	int		check;

	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			check = check_type(str[i + 1], arguments);
			if (check == -1)
				return (-1);
			len += check;
			i++;
		}
		else
		{
			check = ft_putchar_printf(str[i]);
			if (check == -1)
				return (-1);
			len += check;
		}
		i++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	arguments;
	int		output_len;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(arguments, str);
	output_len = check_input(str, arguments, i, len);
	va_end(arguments);
	return (output_len);
}
