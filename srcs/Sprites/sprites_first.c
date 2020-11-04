/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:39:04 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/27 19:39:08 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void		one_sprite(t_all *vars, int *x)
{
	float	fov;
	float	fov_1;

	fov = vars->fov;
	fov_1 = vars->fov;
	while (fov >= 0)
	{
		if ((vars->angle_s - fov_1) > (vars->ang_sprt - vars->d_ang_sprt))
			*x = (int)(((vars->angle_s - fov) -
			(vars->ang_sprt - vars->d_ang_sprt)) / vars->fov_stp);
		if (((vars->ang_sprt - vars->d_ang_sprt - 1) <= (vars->angle_s))
		&& ((vars->ang_sprt + vars->d_ang_sprt + 1) >= (vars->angle_s - fov_1)))
			if ((vars->angle_s - fov) >= (vars->ang_sprt - vars->d_ang_sprt) &&
			(vars->angle_s - fov) <= (vars->ang_sprt + vars->d_ang_sprt))
			{
				if (vars->dist_sprt < (vars->ray)[vars->cnt.cnt_1])
					render_sprt(vars, x);
				(*x)++;
			}
		vars->cnt.cnt_1++;
		fov -= vars->fov_stp;
	}
}

static float	next_one_sprt(t_all *vars, int *x)
{
	*x = 0;
	vars->cur = vars->cur->next;
	vars->cur_cont = vars->cur->content;
	sprite_proc(vars, vars->cur_cont, vars->fov);
	sprt_calc(vars);
	null_cnt(vars);
	return (vars->fov);
}

void			sprite_rdr(t_all *vars)
{
	float	fov;
	int		x;

	fov = vars->fov;
	x = 0;
	null_cnt(vars);
	sort_sprite(vars);
	vars->cur = vars->list_1;
	vars->cur_cont = (t_sprt*)vars->cur->content;
	sprite_proc(vars, vars->cur_cont, fov);
	sprt_calc(vars);
	if ((vars->angle_s - fov) < 0)
		vars->angle_s += 2 * M_PI;
	while (fov >= 0)
	{
		one_sprite(vars, &x);
		if (vars->cur->next)
			fov = next_one_sprt(vars, &x);
		else
			break ;
	}
}
