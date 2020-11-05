/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:15:40 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 20:15:47 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	move_forvard_back(int keycode, t_all *vars)
{
	if (keycode == 13)
	{
		if (vars->pars.map[(int)(vars->loc.y)]
			[(int)(vars->loc.x + 0.3 * cosf(vars->k + vars->angle_r))] != '1')
			vars->loc.x += 0.25 * cosf(vars->k + vars->angle_r);
		if (vars->pars.map[(int)(vars->loc.y
			+ 0.3 * sinf(vars->k + vars->angle_r))]
			[(int)(vars->loc.x)] != '1')
			vars->loc.y += 0.25 * sinf(vars->k + vars->angle_r);
	}
	if (keycode == 1)
	{
		if (vars->pars.map[(int)(vars->loc.y)]
			[(int)(vars->loc.x - 0.3 * cosf(vars->k + vars->angle_r))] != '1')
			vars->loc.x -= 0.25 * cosf(vars->k + vars->angle_r);
		if (vars->pars.map[(int)(vars->loc.y
			- 0.3 * sinf(vars->k + vars->angle_r))]
			[(int)(vars->loc.x)] != '1')
			vars->loc.y -= 0.25 * sinf(vars->k + vars->angle_r);
	}
}

static void	move_left_right(int keycode, t_all *vars, int *a, int *b)
{
	int c;
	int k;

	c = *a;
	k = *b;
	if (keycode == 2)
	{
		if (vars->pars.map[(int)(vars->loc.y)][(int)(vars->loc.x
		- 0.4 * cos(M_PI / k + vars->angle_r) * c)] != '1')
			vars->loc.x -= 0.25 * cos(M_PI / k + vars->angle_r) * c;
		if (vars->pars.map[(int)(vars->loc.y - 0.3 * sin(M_PI / k
		+ vars->angle_r) * c)][(int)(vars->loc.x)] != '1')
			vars->loc.y -= 0.25 * sin(M_PI / k + vars->angle_r) * c;
	}
	if (keycode == 0)
	{
		if (vars->pars.map[(int)(vars->loc.y)][(int)(vars->loc.x
		+ 0.4 * cos(M_PI / k + vars->angle_r) * c)] != '1')
			vars->loc.x += 0.25 * cos(M_PI / k + vars->angle_r) * c;
		if (vars->pars.map[(int)(vars->loc.y + 0.3 * sin(M_PI / k
		+ vars->angle_r) * c)][(int)(vars->loc.x)] != '1')
			vars->loc.y += 0.25 * sin(M_PI / k + vars->angle_r) * c;
	}
}

int			move(int keycode, t_all *vars)
{
	int	c;
	int k;

	c = 1;
	k = 1;
	if (vars->loc.v_vis == 'S' || vars->loc.v_vis == 'E')
		c = -1;
	if (vars->loc.v_vis == 'W' || vars->loc.v_vis == 'E')
		k = 2;
	move_forvard_back(keycode, vars);
	move_left_right(keycode, vars, &c, &k);
	if (keycode == 123)
		vars->angle_r += 355 * M_PI / 180;
	if (keycode == 124)
		vars->angle_r += 5 * M_PI / 180;
	if (keycode == 53)
		otshib_ochka(&vars->pars, -1);
	while (vars->angle_r > 2 * M_PI)
		vars->angle_r -= 2 * M_PI;
	vector_vision(vars);
	return (1);
}
