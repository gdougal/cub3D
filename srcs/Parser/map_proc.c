/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:33:22 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/04 19:26:51 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_unproc(t_cube *cub_st, int *flag)
{
	*flag = 1;
	cub_st->mp = ft_strdup(cub_st->line);
	cub_st->width = (ft_strlen(cub_st->mp) > cub_st->width ?
						ft_strlen(cub_st->mp) + 1 : cub_st->width + 1);
	if (!cub_st->list_f)
		cub_st->list_f = ft_lstnew((char*)cub_st->mp);
	else
		ft_lstadd_back(&cub_st->list_f, ft_lstnew((char *)cub_st->mp));
	cub_st->height++;
}

void		map_proc(t_cube *cub_st, char *argv)
{
	int		fd;
	int		ret;
	int		flag;

	flag = 0;
	ret = 1;
	get_next_line((fd = open(argv, O_RDONLY)), &cub_st->line);
	while (1)
	{
		if (ret != 0 && flag && cub_st->line[0] == '\0' && !cub_st->line)
			otshib_ochka(cub_st, 0);
		else if (flag || cub_st->line[0] == '1'
			|| cub_st->line[0] == ' ' || cub_st->line[0] == '0')
			map_unproc(cub_st, &flag);
		if (cub_st->line)
			free(cub_st->line);
		if (!ret)
			break ;
		ret = get_next_line(fd, &cub_st->line);
	}
	if (!flag)
		otshib_ochka(cub_st, 0);
	map_reproc(cub_st);
}
