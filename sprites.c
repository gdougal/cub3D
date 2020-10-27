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


float	dist_sprt(t_all *vars, t_sprt *tmp)
{
	float	dist;
	dist = sqrtf((vars->locate.x - tmp->x) * (vars->locate.x - tmp->x) + (vars->locate.y - tmp->y) * (vars->locate.y - tmp->y));
	return (dist);
}

void	sprite_sort(t_all *vars)
{
	t_sprt	*tmp;
	t_list	*curnt;
	int		flag;
	float 	dist;

	flag = 0;
	while(!flag)
	{
		flag = 1;
		curnt = vars->list_1;
		tmp = (t_sprt*)vars->list_1->content;
		dist = dist_sprt(vars, tmp);
		while(curnt->next)
		{
			tmp = (t_sprt*)curnt->next->content;
			if (dist > dist_sprt(vars, tmp))
			{
				curnt->next->content = curnt->content;
				curnt->content = tmp;
				flag = 0;
			}
			curnt = curnt->next;
		}
	}
}

void render_sprt(t_all *vars)
{
	vars->cnt.cnt_2 = 0;
	while(vars->cnt.cnt_2 < vars->sprt_start)
		vars->cnt.cnt_2++;
	while(vars->cnt.cnt_2 >= vars->sprt_start && vars->cnt.cnt_2 <= vars->sprt_end)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, 800);
		vars->cnt.cnt_2++;
	}
}


void sprt_calc(t_all *vars)
{
	vars->h_sprt = vars->pars.res_y/vars->dist_sprt;
	vars->w_sprt = vars->pars.res_x/vars->pars.res_y * vars->h_sprt;
	vars->sprt_start = (vars->pars.res_y - vars->h_sprt)/2;
	vars->sprt_end = vars->sprt_start + vars->h_sprt;
}

void 	sprite_proc(t_all *vars, t_sprt *cur_cont)
{

	vars->dist_sprt = dist_sprt(vars, cur_cont);
	vars->d_ang_sprt = atanf(0.5/vars->dist_sprt);
	if (vars->locate.y - cur_cont->y < 0 && vars->locate.x - cur_cont->x < 0)
		vars->ang_sprt = (vars->angle_s > 2*M_PI? 2*M_PI : 0) + atanf((vars->locate.y - cur_cont->y)/(vars->locate.x - cur_cont->x));
	else if(vars->locate.y - cur_cont->y < 0 && vars->locate.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI + atanf((vars->locate.y - cur_cont->y)/(vars->locate.x - cur_cont->x));
	else if(vars->locate.y - cur_cont->y > 0 && vars->locate.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI + atanf((vars->locate.y - cur_cont->y)/(vars->locate.x - cur_cont->x));
	else if (vars->locate.y - cur_cont->y > 0 && vars->locate.x - cur_cont->x < 0)
		vars->ang_sprt = (2*M_PI + atanf((vars->locate.y - cur_cont->y)/(vars->locate.x - cur_cont->x)));

	else if (vars->locate.y - cur_cont->y == 0 && vars->locate.x - cur_cont->x < 0)
		vars->ang_sprt = 2*M_PI;
	else if (vars->locate.y - cur_cont->y == 0 && vars->locate.x - cur_cont->x > 0)
		vars->ang_sprt = M_PI;
	else if (vars->locate.x - cur_cont->x == 0 && vars->locate.y - cur_cont->y < 0)
		vars->ang_sprt = M_PI/2;
	else if (vars->locate.x - cur_cont->x == 0 && vars->locate.y - cur_cont->y > 0)
		vars->ang_sprt = (3*M_PI/2);
}

void	sprite_rdr(t_all *vars)
{
	t_list	*cur;
	t_sprt	*cur_cont;
	float	fov = vars->fov;
	float	fov_stp = fov/vars->pars.res_x;
	float 	fov_1 = vars->fov;

	null_cnt(vars);
	sprite_sort(vars);
	cur = vars->list_1;
	cur_cont = cur->content;
	sprite_proc(vars, cur_cont);
	sprt_calc(vars);
	if ((vars->angle_s - fov) < 0)
		vars->angle_s += 2*M_PI;
	while (fov >= 0)
	{
		while (fov >= 0)
		{
			if (((vars->ang_sprt - vars->d_ang_sprt - 1) <= (vars->angle_s)) && ((vars->ang_sprt + vars->d_ang_sprt + 1)  >= (vars->angle_s - fov_1)))
				if (vars->dist_sprt < (vars->ray)[vars->cnt.cnt_1] && ((vars->angle_s - fov) >= (vars->ang_sprt - vars->d_ang_sprt) && (vars->angle_s - fov) <= (vars->ang_sprt + vars->d_ang_sprt)))
					render_sprt(vars);
			vars->cnt.cnt_1++;
			fov -= fov_stp;
		}
		if(cur->next)
		{
			cur_cont = cur->content;
			fov = vars->fov;
			cur = cur->next;
			sprite_proc(vars, cur_cont);
			sprt_calc(vars);
			null_cnt(vars);
		}
		else
			break;
	}
}

