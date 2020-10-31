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
	if (!(color & 0xFF000000))
		*(unsigned int*)dst = color;
}

unsigned int 	pix_color_txtrs(t_all *vars, int x, int y)
{
	char		 	*dst;
	unsigned int	color;

	dst = vars->txtrs[vars->hit - 1].adr + (y * vars->txtrs[vars->hit - 1].line_length + x * (vars->txtrs[vars->hit - 1].bits_per_pix / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void render_cub(t_all *vars)
{

	if(vars->hit == 2 || vars->hit == 4)
		vars->wall_x = vars->y_1;
	else
		vars->wall_x = vars->x_2;
	vars->wall_x -= floorf(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * vars->txtrs[vars->hit - 1].width);
	if (vars->hit == 1 || vars->hit == 3) vars->tex_x = vars->txtrs[vars->hit - 1].width - vars->tex_x - 1;

	vars->stp = vars->txtrs[vars->hit - 1].height/vars->h_wll;

	vars->txtrs_pos = (vars->w_s - vars->pars.res_y/2 + vars->h_wll/2) * vars->stp;

	while(vars->cnt.cnt_2 < vars->w_s)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->pars.ceilling_clr);
		vars->cnt.cnt_2++;
	}
	while(vars->cnt.cnt_2 >= vars->w_s && vars->cnt.cnt_2 <= vars->w_e)
	{
		vars->tex_y = ((int)(vars->txtrs_pos)) & (vars->txtrs[vars->hit - 1].height - 1);
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, pix_color_txtrs(vars, vars->tex_x, vars->tex_y));
		vars->txtrs_pos += vars->stp;
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
	vars->cnt.cnt_2 = 0;
	vars->h_wll = vars->pars.res_y/vars->dist;
	vars->w_s = (vars->pars.res_y - vars->h_wll)/2;
	vars->w_e = vars->w_s + vars->h_wll;
	if (vars->h_wll > vars->pars.res_y)
	{
		vars->w_s = 0;
		vars->w_e = vars->pars.res_y - 1;
	}
	render_cub(vars);
}

void popravka(t_all *vars)
{
	if (vars->locate.v_vis == 'N')
		vars->k = 3*M_PI/2;
	if (vars->locate.v_vis == 'W')
		vars->k = M_PI;
	if (vars->locate.v_vis == 'S')
		vars->k = M_PI/2;
	if (vars->locate.v_vis == 'E')
		vars->k = 2*M_PI;
}

