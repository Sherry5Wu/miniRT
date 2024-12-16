/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:04:10 by arissane          #+#    #+#             */
/*   Updated: 2024/12/09 10:28:48 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*temp;

	if (count == 0 || size == 0)
		return (NULL);
	if ((count > 0 && (count * size) / count != size)
		|| (size > 0 && (count * size) / size != count))
		return (NULL);
	temp = (void *)malloc(count * size);
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, (count * size));
	return (temp);
}
