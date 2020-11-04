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

# include "cub3d.h"
# include <math.h>

typedef struct	s_location
{
	float		x;
	float		y;
	char		v_vis;
}				t_location;

typedef struct	s_cnt
{
	int			cnt_1;
	int			cnt_2;
}				t_cnt;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_render
{
	void		*mlx;
	void		*mlx_win;
	void		*win;
}				t_render;

typedef struct	s_sprt
{
	float		x;
	float		y;
}				t_sprt;

typedef struct	s_txtrs
{
	void		*img;
	void		*adr;
	int			bits_per_pix;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_txtrs;

typedef	struct	s_all
{
	t_cube		pars;
	t_render	render;
	t_location	loc;
	t_cnt		cnt;
	t_data		img;
	t_list		*list_1;
	t_txtrs		txtrs[6];
	t_list		*cur;
	t_sprt		*cur_cont;
	float		angle_s;
	float		angle_r;
	float		fov;
	float		fov_stp;
	float		k;
	float		dist;
	float		w_s;
	float		w_e;
	float		h_wll;
	float		x_fc;
	float		y_fc;
	float		d_x;
	float		d_y;
	int			hit;
	float		*ray;
	float		x_1;
	float		y_1;
	float		x_2;
	float		y_2;
	float		dist_sprt;
	float		ang_sprt;
	float		d_ang_sprt;
	float		h_sprt;
	float		sprt_start;
	float		sprt_end;
	float		stp;
	float		txtrs_pos;
	int			tex_x;
	float		wall_x;
	int			tex_y;
}				t_all;

t_all			init_vars(t_cube *cube_struct);
#endif
