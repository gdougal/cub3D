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

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# include "get_next_line.h"
# include "libft.h"
# include <stdlib.h>


typedef struct		s_cube_struct
{
    float			res_x;
    float			res_y;
    char			*path[6];
	unsigned int	flor_clr;
    unsigned int	ceilling_clr;
    char 			**map;
    float 			width;
    float 			height;
    int				errno;
    int				lines;
    t_list			*list_f;
    int				player;

}					t_cube_struct;



t_cube_struct		*parser(char *line, char L);
void				go_to_screen(t_cube_struct *cube_struct);// go away tbl Jlishniy
int					create_trgb(int t, int r, int g, int b);
void 				otshib_ochka(t_cube_struct *cub_st);


#endif //CUB3D_PARSER_H
