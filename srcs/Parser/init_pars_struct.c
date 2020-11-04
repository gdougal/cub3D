/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pars_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:20:28 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 15:20:32 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct(t_cube *cub_st)
{
	int i;

	i = 0;
	cub_st->lines = 0;
	cub_st->res_x = -1;
	cub_st->res_y = -1;
	cub_st->flor_clr = 0;
	cub_st->ceilling_clr = 0;
	while (i <= 5)
		cub_st->path[i++] = NULL;
	cub_st->map = NULL;
	cub_st->width = 0;
	cub_st->height = 0;
	cub_st->list_f = NULL;
	cub_st->player = 0;
	cub_st->save = 0;
	cub_st->line = NULL;
}
