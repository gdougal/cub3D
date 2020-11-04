/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:37:35 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 12:37:39 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void		render_sprt(t_all *vars, int *x)
{
	int	y;

	y = 0;
	vars->cnt.cnt_2 = 0;
	if (vars->h_sprt > vars->pars.res_y)
		y = (int)((vars->pars.res_y - vars->h_sprt) / 2 * (-1));
	while (vars->cnt.cnt_2 < vars->sprt_start)
		vars->cnt.cnt_2++;
	while (vars->cnt.cnt_2 >= vars->sprt_start &&
			vars->cnt.cnt_2 <= vars->sprt_end)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2,
			sprite_color_txtrs(vars, (int)(*x * (vars->txtrs[4].
		width / vars->h_sprt)), (int)(y *
		(vars->txtrs[4].height / vars->h_sprt))));
		y += 1;
		vars->cnt.cnt_2++;
	}
}

void		sprt_calc(t_all *vars)
{
	vars->h_sprt = vars->pars.res_y / vars->dist_sprt;
	vars->sprt_start = (vars->pars.res_y - vars->h_sprt) / 2;
	vars->sprt_end = vars->sprt_start + vars->h_sprt;
	if (vars->h_sprt >= vars->pars.res_y)
	{
		vars->sprt_start = 0;
		vars->sprt_end = vars->pars.res_y - 1;
	}
}

static void	podproc(t_all *vars, t_sprt *cur_cont)
{
	if (vars->loc.y - cur_cont->y == 0 && vars->loc.x - cur_cont->x < 0)
		vars->ang_sprt = 2 * M_PI;
	else if (vars->loc.y - cur_cont->y == 0 && vars->loc.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI;
	else if (vars->loc.x - cur_cont->x == 0 && vars->loc.y - cur_cont->y < 0)
		vars->ang_sprt = M_PI / 2;
	else if (vars->loc.x - cur_cont->x == 0 && vars->loc.y - cur_cont->y > 0)
		vars->ang_sprt = (3 * M_PI / 2);
}

void		sprite_proc(t_all *vars, t_sprt *cur_cont, float fov)
{
	vars->dist_sprt = dist_sprt(vars, cur_cont) *
		cosf((vars->angle_s - fov) - (vars->k + vars->angle_r));
	vars->d_ang_sprt = atanf((0.5 * (vars->pars.res_y
			/ vars->pars.res_x)) / vars->dist_sprt);
	if (vars->loc.y - cur_cont->y < 0 && vars->loc.x - cur_cont->x < 0)
		vars->ang_sprt = (vars->angle_s > 2 * M_PI ? 2 * M_PI : 0) +
		atanf((vars->loc.y - cur_cont->y) / (vars->loc.x - cur_cont->x));
	else if (vars->loc.y - cur_cont->y < 0 && vars->loc.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI + atanf((vars->loc.y - cur_cont->y) /
				(vars->loc.x - cur_cont->x));
	else if (vars->loc.y - cur_cont->y > 0 && vars->loc.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI + atanf((vars->loc.y - cur_cont->y) /
				(vars->loc.x - cur_cont->x));
	else if (vars->loc.y - cur_cont->y > 0 && vars->loc.x - cur_cont->x < 0)
		vars->ang_sprt = (2 * M_PI + atanf((vars->loc.y - cur_cont->y) /
				(vars->loc.x - cur_cont->x)));
	podproc(vars, cur_cont);
}
