/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buble_sort_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 10:37:52 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 10:37:54 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	dist_sprt(t_all *vars, t_sprt *tmp)
{
	float	dist;

	dist = sqrtf(powf((vars->loc.x - tmp->x), 2)
			+ powf((vars->loc.y - tmp->y), 2));
	return (dist);
}

void	swap(t_list *a, t_list *b)
{
	t_sprt *temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	sort_sprite(t_all *vars)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;

	lptr = NULL;
	while (1)
	{
		swapped = 0;
		ptr1 = vars->list_1;
		while (ptr1->next != lptr)
		{
			if (dist_sprt(vars, ptr1->content) <
				dist_sprt(vars, ptr1->next->content))
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
		if (!swapped)
			break ;
	}
}
