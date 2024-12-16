/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:47:09 by arissane          #+#    #+#             */
/*   Updated: 2024/05/07 12:47:14 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*nodecpy;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	newlst = NULL;
	while (lst != NULL)
	{
		temp = f(lst->content);
		nodecpy = ft_lstnew(temp);
		if (nodecpy == NULL)
		{
			del(temp);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, nodecpy);
		lst = lst->next;
	}
	return (newlst);
}
