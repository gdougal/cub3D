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
#include "struct.h"

void		my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color);
int			move(int keycode, t_all *vars);
void		render_cub(t_all *vars);
void		wall_calc(t_all *vars);
void		popravka(t_all *vars);

#endif //UNTITLED_RENDER_H
