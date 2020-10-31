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
# include <stdio.h>


float	dist_sprt(t_all *vars, t_sprt *tmp)
{
	float	dist;
	dist = sqrtf((vars->locate.x - tmp->x) * (vars->locate.x - tmp->x) + (vars->locate.y - tmp->y) * (vars->locate.y - tmp->y));
	return (dist);
}

void swap(t_list *a, t_list *b)
{
	t_sprt *temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void bubbleSort(t_all *vars)
{
	int		swapped;
	t_list *ptr1;
	t_list *lptr = NULL;

	do
	{
		swapped = 0;
		ptr1 = vars->list_1;

		while (ptr1->next != lptr)
		{
			if (dist_sprt(vars, ptr1->content) < dist_sprt(vars, ptr1->next->content))
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	while (swapped);
}


unsigned int 	sprite_color_txtrs(t_all *vars, int x, int y)
{
	char		 	*dst;
	unsigned int	color;

	dst = vars->txtrs[4].adr + (y * vars->txtrs[4].line_length + x * (vars->txtrs[4].bits_per_pix / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void render_sprt(t_all *vars, int *x)
{
	int	y = 0;

	vars->cnt.cnt_2 = 0;
	if(vars->h_sprt > vars->pars.res_y)
		y = (int)((vars->pars.res_y - vars->h_sprt)/2 * (-1));
	while(vars->cnt.cnt_2 < vars->sprt_start)
		vars->cnt.cnt_2++;
	while(vars->cnt.cnt_2 >= vars->sprt_start && vars->cnt.cnt_2 <= vars->sprt_end)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, sprite_color_txtrs(vars, (int)(*x*(vars->txtrs[4].width/vars->h_sprt)), (int)(y*(vars->txtrs[4].height/vars->h_sprt))));
		y += 1;
		vars->cnt.cnt_2++;
	}
}


void sprt_calc(t_all *vars)
{
	vars->h_sprt = vars->pars.res_y/vars->dist_sprt;
	vars->sprt_start = (vars->pars.res_y - vars->h_sprt)/2;
	vars->sprt_end = vars->sprt_start + vars->h_sprt;
	if (vars->h_sprt >= vars->pars.res_y)
	{
		vars->sprt_start = 0;
		vars->sprt_end = vars->pars.res_y - 1;
	}
}

void 	sprite_proc(t_all *vars, t_sprt *cur_cont, float fov)
{

	vars->dist_sprt = dist_sprt(vars, cur_cont) * cosf((vars->angle_s - fov) - (vars->k + vars->angle_r));
	vars->d_ang_sprt = atanf((0.5*(vars->pars.res_y/vars->pars.res_x))/vars->dist_sprt);
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
	int		x = 0;

	null_cnt(vars);
	bubbleSort(vars);
	cur = vars->list_1;
	cur_cont = (t_sprt*)cur->content;
	sprite_proc(vars, cur_cont, fov);
	sprt_calc(vars);
	if ((vars->angle_s - fov) < 0)
		vars->angle_s += 2*M_PI;
	while (fov >= 0)
	{
		while (fov >= 0)
		{
			if((vars->angle_s - fov_1) > (vars->ang_sprt - vars->d_ang_sprt))
				x = (int)(((vars->angle_s - fov) - (vars->ang_sprt - vars->d_ang_sprt))/fov_stp);
			if (((vars->ang_sprt - vars->d_ang_sprt - 1) <= (vars->angle_s)) && ((vars->ang_sprt + vars->d_ang_sprt + 1)  >= (vars->angle_s - fov_1)))
				if ((vars->angle_s - fov) >= (vars->ang_sprt - vars->d_ang_sprt) && (vars->angle_s - fov) <= (vars->ang_sprt + vars->d_ang_sprt))
				{
					if (vars->dist_sprt < (vars->ray)[vars->cnt.cnt_1])
						render_sprt(vars, &x);
					x++;
				}
			vars->cnt.cnt_1++;
			fov -= fov_stp;
		}
		if(cur->next)
		{
			fov = vars->fov;
			x = 0;
			cur = cur->next;
			cur_cont = cur->content;
			sprite_proc(vars, cur_cont, fov);
			sprt_calc(vars);
			null_cnt(vars);
		}
		else
			break;
	}
}