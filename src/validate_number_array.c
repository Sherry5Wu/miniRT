/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_number_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:19:21 by arissane          #+#    #+#             */
/*   Updated: 2025/01/30 10:25:43 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	validate_number_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	non_integer_checking(char *str, int i)
{
	while (str[i] && str[i] != '.')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_decimal_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	if (non_integer_checking(str, i) == 1)
		return (1);
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (1);
			i++;
		}
	}
	return (0);
}

int	validate_number_array(char **array, int type)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (type == 1)
		{
			if (validate_number_string(array[i]) == 1)
				return (1);
		}
		if (type == 2)
		{
			if (validate_decimal_string(array[i]) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
