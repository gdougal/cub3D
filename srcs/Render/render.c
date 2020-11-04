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

static void	prerender(t_all *vars)
{
	if (vars->hit == 2 || vars->hit == 4)
		vars->wall_x = vars->y_1;
	else
		vars->wall_x = vars->x_2;
	vars->wall_x -= floorf(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * vars->txtrs[vars->hit - 1].width);
	if (vars->hit == 1 || vars->hit == 3)
		vars->tex_x = vars->txtrs[vars->hit - 1].width - vars->tex_x - 1;
	vars->stp = vars->txtrs[vars->hit - 1].height / vars->h_wll;
	vars->txtrs_pos = (vars->w_s - vars->pars.res_y
			/ 2 + vars->h_wll / 2) * vars->stp;
}

static void	render_cub(t_all *vars, t_cnt *cnt)
{
	prerender(vars);
	while (cnt->cnt_2 < vars->w_s)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1,
			vars->cnt.cnt_2, vars->pars.ceilling_clr);
		vars->cnt.cnt_2++;
	}
	while (cnt->cnt_2 >= vars->w_s && cnt->cnt_2 <= vars->w_e)
	{
		vars->tex_y = ((int)(vars->txtrs_pos)) &
				(vars->txtrs[vars->hit - 1].height - 1);
		my_mlx_pixel_put(vars, cnt->cnt_1, cnt->cnt_2,
			pix_color_txtrs(vars, vars->tex_x, vars->tex_y));
		vars->txtrs_pos += vars->stp;
		cnt->cnt_2++;
	}
	while (cnt->cnt_2 > vars->w_e && cnt->cnt_2 < vars->pars.res_y)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1,
			cnt->cnt_2, vars->pars.flor_clr);
		cnt->cnt_2++;
	}
}

void		wall_calc(t_all *vars)
{
	vars->cnt.cnt_2 = 0;
	vars->h_wll = vars->pars.res_y / vars->dist;
	vars->w_s = (vars->pars.res_y - vars->h_wll) / 2;
	vars->w_e = vars->w_s + vars->h_wll;
	if (vars->h_wll > vars->pars.res_y)
	{
		vars->w_s = 0;
		vars->w_e = vars->pars.res_y - 1;
	}
	render_cub(vars, &vars->cnt);
}
