/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distantion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:48:44 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 14:48:46 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void		poddist_x(t_all *vars, float fov, float *k)
{
	vars->d_x = fabsf(vars->loc.x - (vars->x_fc + *k));
	if (cosf(vars->angle_s - fov) < 0)
	{
		vars->d_y = vars->d_x * ((-1) * tanf(vars->angle_s - fov));
		vars->x_1 = vars->loc.x - vars->d_x;
		*k -= 1;
	}
	else
	{
		vars->d_y = vars->d_x * (tanf(vars->angle_s - fov));
		vars->x_1 = vars->loc.x + vars->d_x;
		*k += 1;
	}
	vars->y_1 = vars->loc.y + (vars->d_y);
}

static float	dist_x(t_all *vars, float fov)
{
	float	k;
	int		hit;

	k = 0;
	hit = 0;
	while (!hit)
	{
		poddist_x(vars, fov, &k);
		if (vars->y_1 < 0 || vars->y_1 > (float)vars->pars.height
						|| vars->x_1 >= (float)vars->pars.width)
			break ;
		if (vars->x_1 >= 1 && cosf(vars->angle_s - fov) < 0 &&
		vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1 - 1)] == '1')
			hit = 1;
		else if (cosf(vars->angle_s - fov) > 0 &&
		vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1)] == '1')
			hit = 2;
	}
	return (dist_wall(vars->x_1, vars->loc.x, vars->y_1, vars->loc.y));
}

static void		poddist_y(t_all *vars, float fov, float *k)
{
	vars->d_y = fabsf(vars->loc.y - (vars->y_fc + *k));
	if (sinf(vars->angle_s - fov) < 0)
	{
		vars->d_x = vars->d_y * ((-1) * 1 / tanf(vars->angle_s - fov));
		vars->y_2 = vars->loc.y - fabsf(vars->d_y);
		*k -= 1;
	}
	else
	{
		vars->d_x = vars->d_y * (1 / tanf(vars->angle_s - fov));
		vars->y_2 = vars->loc.y + fabsf(vars->d_y);
		*k += 1;
	}
	vars->x_2 = vars->loc.x + (vars->d_x);
}

static float	dist_y(t_all *vars, float fov)
{
	float	k;
	int		hit;

	k = 0;
	hit = 0;
	while (!hit)
	{
		poddist_y(vars, fov, &k);
		if (vars->x_2 < 0 || vars->x_2 > vars->pars.width
			|| vars->y_2 >= vars->pars.height)
			break ;
		if (vars->y_2 >= 1 && sinf(vars->angle_s - fov) < 0
			&& vars->pars.map[(int)(vars->y_2 - 1)][(int)(vars->x_2)] == '1')
			hit = 3;
		else if (sinf(vars->angle_s - fov) > 0 &&
		vars->pars.map[(int)(vars->y_2)][(int)(vars->x_2)] == '1')
			hit = 4;
	}
	return (dist_wall(vars->x_2, vars->loc.x, vars->y_2, vars->loc.y));
}

void			calc_del_x_y(t_all *vars, float fov)
{
	float	dst_x;
	float	dst_y;

	if (cosf(vars->angle_s - fov) < 0)
		vars->x_fc = floorf(vars->loc.x);
	else
		vars->x_fc = ceilf(vars->loc.x);
	if (sinf(vars->angle_s - fov) < 0)
		vars->y_fc = floorf(vars->loc.y);
	else
		vars->y_fc = ceilf(vars->loc.y);
	null_x_y(vars);
	dst_x = dist_x(vars, fov);
	dst_y = dist_y(vars, fov);
	what_a_side(vars, dst_x, dst_y, fov);
	vars->dist = (dst_x <= dst_y ? dst_x : dst_y) *
		cosf((vars->angle_s - fov) - (vars->k + vars->angle_r));
	wall_calc(vars);
	(vars->ray)[vars->cnt.cnt_1] = vars->dist;
	vars->cnt.cnt_1++;
}
