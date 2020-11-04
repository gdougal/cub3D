/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 11:56:14 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:57:12 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*head;

	if (!lst || !(n_lst = ft_lstnew(f(lst->content))))
		return (NULL);
	head = n_lst;
	while (lst->next)
	{
		lst = lst->next;
		n_lst->next = ft_lstnew(f(lst->content));
		if (!n_lst->next)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		n_lst = n_lst->next;
	}
	return (head);
}
