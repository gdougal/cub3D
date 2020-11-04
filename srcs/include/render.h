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

# include <mlx.h>
# include "struct.h"

void			my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color);

void			pers_position(t_all *vars, t_cube *pars, t_cnt *cnt);
int				move(int keycode, t_all *vars);

void			popravka(t_all *vars);
void			vector_vision(t_all *vars);
void			wall_calc(t_all *vars);
void			what_a_side(t_all *vars, float dst_x, float dst_y, float fov);
void			calc_del_x_y(t_all *vars, float fov);
void			null_x_y(t_all *vars);
float			dist_wall(float x1, float x0, float y1, float y0);

unsigned int	pix_color_txtrs(t_all *vars, int x, int y);
void			sort_sprite(t_all *vars);
float			dist_sprt(t_all *vars, t_sprt *tmp);
void			sprite_rdr(t_all *vars);
void			sprite_proc(t_all *vars, t_sprt *cur_cont, float fov);
void			sprt_calc(t_all *vars);
void			render_sprt(t_all *vars, int *x);
unsigned int	sprite_color_txtrs(t_all *vars, int x, int y);

void			screenshoot(t_all *vars);
void			null_cnt(t_all *vars);

int				otshib_ochka_x(t_cube *cub_st);
#endif
