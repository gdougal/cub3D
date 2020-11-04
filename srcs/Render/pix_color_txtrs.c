/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_color_txtrs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:32:38 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 11:32:40 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned int	pix_color_txtrs(t_all *vars, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = vars->txtrs[vars->hit - 1].adr + (y * vars->txtrs[vars->hit - 1].
			line_length + x * (vars->txtrs[vars->hit - 1].bits_per_pix / 8));
	color = *(unsigned int*)dst;
	return (color);
}
