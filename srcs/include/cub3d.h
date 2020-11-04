/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:21:10 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:21:13 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../gnl/get_next_line.h"
# include "../../libs/libft/libft.h"

typedef struct		s_cube_struct
{
	float			res_x;
	float			res_y;
	char			*path[6];
	unsigned int	flor_clr;
	unsigned int	ceilling_clr;
	char			**map;
	float			width;
	float			height;
	int				lines;
	t_list			*list_f;
	int				player;
	char			*mp;
	char			**tmp;
	int				save;
	char			*line;

}					t_cube;

void				chek_type_first_arg(char *arg, t_cube *cub_st);
void				init_struct(t_cube *cub_st);
void				proc_numbers(char *line, char l, t_cube *cub_st);
void				color_check(t_cube *cub_st);
void				proc_path(char *line, char l, t_cube *cub_st);
void				map_proc(float height, t_cube *cub_st, char *argv);

void				valid_sym_map(char *tmp, t_cube *cub_st);
void				map_val(t_cube *cub_st);
void				map_reproc(t_cube *cub_st);

void				go_to_screen(t_cube *cube_struct);
int					create_trgb(int t, int r, int g, int b);
void				otshib_ochka(t_cube *cub_st, int errno);

#endif
