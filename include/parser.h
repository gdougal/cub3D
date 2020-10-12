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
	t_cube_struct 	*pars;
	t_render		render;
	t_location		*locate;
	t_cnt			*cnt;
	t_data			img;
}               t_all;

t_cube_struct		*parser(char *line, char L);
int					move(int keycode, t_all *vars);
void			go_to_screen(t_cube_struct *cube_struct);// go away tbl Jlishniy


#endif //CUB3D_PARSER_H
