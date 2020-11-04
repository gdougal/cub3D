/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:28:11 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 11:28:15 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.line_length + x
			* (vars->img.bits_per_pixel / 8));
	if (!(color & 0xFF000000))
		*(unsigned int*)dst = color;
}
