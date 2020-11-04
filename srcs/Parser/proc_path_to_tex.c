/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_path_to_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:30:38 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 15:30:43 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	proc_path(char *line, char l, t_cube *cub_st)
{
	if (l == 'N')
		cub_st->path[0] = ft_strtrim(line, "NO ");
	else if (l == 'S')
		cub_st->path[2] = ft_strtrim(line, "SO ");
	else if (l == 'W')
		cub_st->path[3] = ft_strtrim(line, "WE ");
	else if (l == 'E')
		cub_st->path[1] = ft_strtrim(line, "EA ");
	else if (l == 's')
		cub_st->path[4] = ft_strtrim(line, "S ");
	cub_st->lines++;
}
