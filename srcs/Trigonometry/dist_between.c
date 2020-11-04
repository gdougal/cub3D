/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_between.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:34:42 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 15:34:44 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	dist_wall(float x1, float x0, float y1, float y0)
{
	float	dist;

	dist = sqrtf(powf((x1 - x0), 2) + powf((y1 - y0), 2));
	return (dist);
}
