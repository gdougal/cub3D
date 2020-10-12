/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:21:20 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:21:22 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNTITLED_STRUCT_H
# define UNTITLED_STRUCT_H

# include "parser.h"

typedef struct		s_location
{
	int             x;
	int				y;
	int             eq;
}					t_location;

typedef struct  s_cnt {
	int 			cnt_1;
	int 			cnt_2;
	int 			cnt_3;
	int 			cnt_4;
}               t_cnt;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_render {
	void        *mlx;
	void        *mlx_win;
	void        *win;
}               t_render;

typedef struct  s_all {
	t_cube_struct 	pars;
	t_render		render;
	t_location		locate;
	t_cnt			cnt;
	t_data			img;
}               t_all;


t_all 	init_vars(t_cube_struct *cube_struct);
static void	init_render_img(t_render *render, t_data *img);
static void	init_location_counter(t_location *location, t_cnt *cnt);
#endif //UNTITLED_STRUCT_H
