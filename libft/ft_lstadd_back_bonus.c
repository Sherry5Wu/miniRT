/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:40:20 by arissane          #+#    #+#             */
/*   Updated: 2024/05/07 12:40:26 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*final;

	if (!lst || !new)
		return ;
	final = (*lst);
	if (!final)
	{
		*lst = new;
		return ;
	}
	while (final->next)
		final = final->next;
	final->next = new;
}
