/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:52:48 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/02 11:52:51 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	popravka(t_all *vars)
{
	if (vars->loc.v_vis == 'N')
		vars->k = 3 * M_PI / 2;
	if (vars->loc.v_vis == 'W')
		vars->k = M_PI;
	if (vars->loc.v_vis == 'S')
		vars->k = M_PI / 2;
	if (vars->loc.v_vis == 'E')
		vars->k = 2 * M_PI;
}
