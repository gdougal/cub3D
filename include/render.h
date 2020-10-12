/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:43:21 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:43:23 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UNTITLED_RENDER_H
# define UNTITLED_RENDER_H

#include <mlx.h>
#include <math.h>
#include "struct.h"

void render_map(t_all *vars);
static void put_pixel_map(t_all *vars);
void put_pers(t_all *vars);
void	my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color);
int					move(int keycode, t_all *vars);
void clear_pers(t_all *vars);

#endif //UNTITLED_RENDER_H
