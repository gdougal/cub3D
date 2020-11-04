/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reproc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:42:28 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 18:42:30 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	del(void *content)
{
	if (content)
	{
		free(content);
		content = NULL;
	}
}

void		map_reproc(t_cube *cub_st)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = cub_st->list_f;
	if (!(cub_st->map = (char **)malloc(sizeof(char *)
			* (int)(cub_st->height))))
		otshib_ochka(cub_st, 0);
	while (i < (int)cub_st->height)
		cub_st->map[i++] = ft_calloc((cub_st->width), sizeof(char));
	cub_st->map[i] = NULL;
	i = 0;
	while (tmp)
	{
		valid_sym_map((char *)tmp->content, cub_st);
		ft_strlcpy(cub_st->map[i], tmp->content, (ft_strlen(tmp->content) + 1));
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&cub_st->list_f, del);
	if (cub_st->player != 1)
		otshib_ochka(cub_st, 0);
	map_val(cub_st);
}
