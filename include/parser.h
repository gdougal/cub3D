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

//# define FLAG_MINUS (0b00000001u)
//# define FLAG_ZERO	(0b00000010u)

# include "get_next_line.h"
# include "libft.h"

typedef struct		s_cube_struct
{
    int             res_x;
    int				res_y;
    char			*path_n;
    char			*path_s;
    char			*path_w;
    char			*path_e;
    char			*path_sprite;
	unsigned int	flor_clr;
    unsigned int	ceilling_clr;
    char 			**map;

    int 			width;
    int 			height;

}					t_cube_struct;



t_cube_struct		*parser(char *line, char L);
void			go_to_screen(t_cube_struct *cube_struct);// go away tbl Jlishniy


#endif //CUB3D_PARSER_H
