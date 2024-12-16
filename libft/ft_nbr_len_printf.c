/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_len_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:41:48 by arissane          #+#    #+#             */
/*   Updated: 2024/05/23 11:06:48 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_nbr_len_printf(long val, char c)
{
	int	len;

	len = 0;
	if (c == 'x' || c == 'X')
	{
		while (val > 0)
		{
			val = val / 16;
			len++;
		}
	}
	if (c == 'd' || c == 'i' || c == 'u')
	{
		if (val < 0)
		{
			val = -val;
			len++;
		}
		while (val > 0)
		{
			val = val / 10;
			len++;
		}
	}
	return (len);
}
