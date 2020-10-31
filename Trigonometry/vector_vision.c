/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 20:53:40 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/24 20:53:43 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
# include <stdio.h>


void	what_a_side(t_all *vars, float dst_x, float dst_y, float fov)
{
	if(dst_y < dst_x && sinf(vars->angle_s - fov) < 0)
		vars->hit = 1;
	else if(dst_x < dst_y && cosf(vars->angle_s - fov) > 0)
		vars->hit = 2;
	else if(dst_y < dst_x && sinf(vars->angle_s - fov) > 0)
		vars->hit = 3;
	else if(dst_x < dst_y && cosf(vars->angle_s - fov) < 0)
		vars->hit = 4;
}

float	dist_x(t_all *vars, float fov)
{
	float 	k = 0;
	int		hit = 0;
	vars->x_1 = 0;
	vars->y_1 = 0;

	while(!hit)
	{
		vars->d_x = fabsf(vars->locate.x - (vars->x_fc + k));
		if (cosf(vars->angle_s - fov) < 0)
		{
			vars->d_y = vars->d_x * ((-1) * tanf(vars->angle_s - fov));
			vars->x_1 = vars->locate.x - vars->d_x;
			k -= 1;
		}
		else
		{
			vars->d_y = vars->d_x * (tanf(vars->angle_s - fov));
			vars->x_1 = vars->locate.x + vars->d_x;
			k += 1;
		}
		vars->y_1 = vars->locate.y + (vars->d_y);
		if (vars->y_1 < 0 || vars->y_1 > (float)vars->pars.height || vars->x_1 >= (float)vars->pars.width)
			break;
		if (vars->x_1 >= 1 && cosf(vars->angle_s - fov) < 0 && vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1 - 1)] == '1')
			hit = 1;
		else if (cosf(vars->angle_s - fov) > 0 && vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1)] == '1')
			hit = 2;
	}
	return (sqrtf((vars->x_1 - vars->locate.x)*(vars->x_1 - vars->locate.x) + (vars->y_1 - vars->locate.y)*(vars->y_1 - vars->locate.y)));
}

float	dist_y(t_all *vars, float fov)
{
	float 	k = 0;
	int		hit = 0;
	vars->x_2 = 0;
	vars->y_2 = 0;

	while(!hit)
	{
		vars->d_y = fabsf(vars->locate.y - (vars->y_fc + k));
		if (sinf(vars->angle_s - fov) < 0)
		{
			vars->d_x = vars->d_y * ((-1) * 1 / tanf(vars->angle_s - fov));
			vars->y_2 = vars->locate.y - fabsf(vars->d_y);
			k -= 1;
		}
		else
		{
			vars->d_x = vars->d_y * (1 / tanf(vars->angle_s - fov));
			vars->y_2 = vars->locate.y + fabsf(vars->d_y);
			k += 1;
		}
		vars->x_2 = vars->locate.x + (vars->d_x);
		if (vars->x_2 < 0 || vars->x_2 > vars->pars.width ||  vars->y_2 >= vars->pars.height)
			break;
		if (vars->y_2 >= 1 && sinf(vars->angle_s - fov) < 0 && vars->pars.map[(int)(vars->y_2 - 1)][(int)(vars->x_2)] == '1')
			hit = 3;
		else if(sinf(vars->angle_s - fov) > 0 && vars->pars.map[(int)(vars->y_2)][(int)(vars->x_2)] == '1')
			hit = 4;
	}
	return (sqrtf((vars->x_2 - vars->locate.x)*(vars->x_2 - vars->locate.x) + (vars->y_2 - vars->locate.y)*(vars->y_2 - vars->locate.y)));
}

void	calc_del_x_y(t_all *vars, float fov)
{
	float	dst_x;
	float	dst_y;
	if (cosf(vars->angle_s - fov) < 0)
		vars->x_fc = floorf(vars->locate.x);
	else
		vars->x_fc = ceilf(vars->locate.x);
	if (sinf(vars->angle_s - fov) < 0)
		vars->y_fc = floorf(vars->locate.y);
	else
		vars->y_fc = ceilf(vars->locate.y);
	dst_x = dist_x(vars, fov);
	dst_y = dist_y(vars, fov);
	what_a_side(vars, dst_x, dst_y, fov);
	vars->dist = (dst_x <= dst_y ? dst_x : dst_y) * cosf((vars->angle_s - fov) - (vars->k + vars->angle_r));
}


void	vector_vision(t_all *vars)
{
	float	fov = vars->fov;
	float	fov_2 = fov/2;
	float	fov_stp = fov/vars->pars.res_x;

	null_cnt(vars);
	popravka(vars);
	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
	while((vars->angle_s - fov) >= 2*M_PI)
		vars->angle_s -= 2*M_PI;
	while (fov >= 0)
	{
		vars->dist = 0;
		calc_del_x_y(vars, fov);
		wall_calc(vars);
		(vars->ray)[vars->cnt.cnt_1] = vars->dist;
		vars->cnt.cnt_1++;
		fov -= fov_stp;
	}
	if (vars->list_1)
		sprite_rdr(vars);
	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
}

