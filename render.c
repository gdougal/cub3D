/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:44:11 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:44:13 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "struct.h"

void	my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color)
{
	char    *dst;

	dst = vars->img.addr + (y * vars->img.line_length + x * (vars->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void render_cub(t_all *vars)
{
	vars->cnt.cnt_2 = 0;
	while(vars->cnt.cnt_2 < vars->w_s)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->pars.ceilling_clr);
		vars->cnt.cnt_2++;
	}
	while(vars->cnt.cnt_2 >= vars->w_s && vars->cnt.cnt_2 <= vars->w_e)
	{
		if(vars->hit == 1)
			my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->w_1_color);
		else if(vars->hit == 2)
			my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->w_2_color);
		else if(vars->hit == 3)
			my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->w_3_color);
		else if(vars->hit == 4)
			my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->w_4_color);

		vars->cnt.cnt_2++;
	}
	while(vars->cnt.cnt_2 > vars->w_e && vars->cnt.cnt_2 < vars->pars.res_y - 1)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->pars.flor_clr);
		vars->cnt.cnt_2++;
	}
}

void wall_calc(t_all *vars)
{
	vars->h_wll = vars->pars.res_y/vars->dist;
	vars->w_s = (vars->pars.res_y - vars->h_wll)/2;
	vars->w_e = vars->w_s + vars->h_wll;
	render_cub(vars);
}

void popravka(t_all *vars)
{
	if (vars->locate.v_vis == 'N')
		vars->k = 3*M_PI/2;
	if (vars->locate.v_vis == 'W')
		vars->k = M_PI;
	if (vars->locate.v_vis == 'S')
		vars->k = 3*M_PI/2;
	if (vars->locate.v_vis == 'E')
		vars->k = 0;
}

