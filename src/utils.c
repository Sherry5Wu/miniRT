/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:11:38 by arissane          #+#    #+#             */
/*   Updated: 2025/01/13 13:28:04 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	write_error(char *str)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static float	get_fraction(char *str, double number)
{
	int		i;
	double	fraction;
	double	divisor;

	i = 0;
	fraction = 0.0;
	divisor = 10.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (fraction > FLOAT_MAX)
			return (FLOAT_MAX);
		fraction = fraction + ((str[i] - 48) / divisor);
		divisor = 10.0 * divisor;
		i++;
	}
	return (number + fraction);
}

float	ft_atofloat(char *str)
{
	int		i;
	double	number;
	double	sign;

	i = 0;
	number = 0.0;
	sign = 1.0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > FLOAT_MAX)
			break ;
		number = number * 10.0 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
		number = get_fraction(&str[i + 1], number);
	if (number >= FLOAT_MAX)
		return (FLOAT_MAX);
	return ((float)(sign * number));
}
