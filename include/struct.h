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
# include <math.h>

typedef struct		s_location
{
	double			x;
	double			y;
//	int             eq;
	char 			v_vis;
}					t_location;

typedef struct		s_cnt {
	int 			cnt_1;
	int				cnt_2;
//	int 			cnt_3;
//	int 			cnt_4;
}					t_cnt;

typedef struct		s_data {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct		s_render {
	void			*mlx;
	void			*mlx_win;
	void			*win;
}					t_render;

typedef struct		s_all
{
	t_cube_struct	pars;
	t_render		render;
	t_location		locate;
	t_cnt			cnt;
	t_data			img;

	double			angle_s;
	double			angle_r;
	double 			fov;
	double			k;

	double 			dist;
	unsigned int 	w_1_color;
	unsigned int 	w_2_color;
	unsigned int 	w_3_color;
	unsigned int 	w_4_color;
	double			w_s;
	double			w_e;
	double			h_wll;

	double			x_fc;
	double			x_1;
	double			y_1;
	double			x_2;
	double			y_2;
	double 			y_fc;
	double			d_x;
	double 			d_y;
	int				hit;


}					t_all;


t_all 		init_vars(t_cube_struct *cube_struct);
static void	init_render_img(t_render *render, t_data *img);
static void	init_location_counter(t_location *location, t_cnt *cnt);
void		null_cnt(t_all *vars);
#endif //UNTITLED_STRUCT_H
