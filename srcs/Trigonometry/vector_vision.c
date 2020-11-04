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

void	vector_vision(t_all *vars)
{
	float	fov;
	float	fov_2;

	fov = vars->fov;
	fov_2 = fov / 2;
	null_cnt(vars);
	popravka(vars);
	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
	while ((vars->angle_s - fov) >= 2 * M_PI)
		vars->angle_s -= 2 * M_PI;
	while (fov >= 0)
	{
		vars->dist = 0;
		calc_del_x_y(vars, fov);
		fov -= vars->fov_stp;
	}
	if (vars->list_1)
		sprite_rdr(vars);
	mlx_put_image_to_window(vars->render.mlx,
		vars->render.mlx_win, vars->img.img, 0, 0);
}
