/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:45:11 by arissane          #+#    #+#             */
/*   Updated: 2024/05/11 09:01:57 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*templst;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		templst = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = templst;
	}
	free(*lst);
	*lst = NULL;
}
