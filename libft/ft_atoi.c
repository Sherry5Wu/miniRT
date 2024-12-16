/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:39:50 by arissane          #+#    #+#             */
/*   Updated: 2024/12/09 11:39:53 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long long int	check_number(const char *str, long long int i,
								long long int number, int sign)
{
	long long int	check;

	while (str[i] >= '0' && str[i] <= '9')
	{
		check = number;
		number = number * 10;
		if (sign == 1 && check != (number / 10))
			return (-1);
		if (sign == -1 && check != (number / 10))
			return (0);
		number = number + (str[i] - 48);
		i++;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	long long int	i;
	long long int	number;
	int				sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
		number = check_number(str, i, number, sign);
	return (sign * number);
}
