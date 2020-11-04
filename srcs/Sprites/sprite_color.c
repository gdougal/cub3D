/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:42:23 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 12:42:27 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned int	sprite_color_txtrs(t_all *vars, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = vars->txtrs[4].adr + (y * vars->txtrs[4].line_length
			+ x * (vars->txtrs[4].bits_per_pix / 8));
	color = *(unsigned int*)dst;
	return (color);
}
