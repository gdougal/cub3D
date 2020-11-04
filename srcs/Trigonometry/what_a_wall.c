/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_a_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:45:54 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 14:45:55 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	what_a_side(t_all *vars, float dst_x, float dst_y, float fov)
{
	if (dst_y < dst_x && sinf(vars->angle_s - fov) < 0)
		vars->hit = 1;
	else if (dst_x < dst_y && cosf(vars->angle_s - fov) > 0)
		vars->hit = 2;
	else if (dst_y < dst_x && sinf(vars->angle_s - fov) > 0)
		vars->hit = 3;
	else if (dst_x < dst_y && cosf(vars->angle_s - fov) < 0)
		vars->hit = 4;
}
