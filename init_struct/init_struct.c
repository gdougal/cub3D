/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:31:09 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:31:10 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parser.h"



static void	init_location_counter(t_location *location, t_cnt *cnt)
{
	location->x = 0;
	location->y = 0;
	location->eq = 0;
	location->v_vis = 'A';

	cnt->cnt_1 = 0;
	cnt->cnt_2 = 0;
	cnt->cnt_4 = 0;
	cnt->cnt_3 = 0;
}

static void	init_render_img(t_render *render, t_data *img)
{
	render->mlx = NULL;
	render->mlx_win = NULL;
	render->win = NULL;

	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
}

t_all 	init_vars(t_cube_struct *cube_struct)
{
	t_all		vars;
	t_render 	render;
	t_data 		img;
	t_location	location;
	t_cnt 		cnt;

	init_render_img(&render, &img);
	init_location_counter(&location, &cnt);

	vars.locate = location;
	vars.pars = *cube_struct;
	vars.render = render;
	vars.img = img;
	vars.cnt = cnt;
	vars.locate.eq = ((vars.pars.res_y/vars.pars.height) < (vars.pars.res_x/vars.pars.width) ?
					  (vars.pars.res_y/vars.pars.height) : (vars.pars.res_x/vars.pars.width));
	vars.fov = 45;
	return (vars);
}
