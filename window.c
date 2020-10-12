/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:53:23 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/09 17:53:26 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <mlx.h>
#include <stdio.h>

// Struct with counters



void	init_vars_2(t_all *vars)
{
	vars->cnt->cnt_1 = 0;
	vars->cnt->cnt_2 = 0;
	vars->cnt->cnt_4 = 0;
	vars->cnt->cnt_3 = 0;
	vars->locate->eq = ((vars->pars->res_y/vars->pars->height) < (vars->pars->res_x/vars->pars->width) ?
						(vars->pars->res_y/vars->pars->height) : (vars->pars->res_x/vars->pars->width));
	vars->locate->x = 0;
	vars->locate->y = 0;
}

t_all 	init_vars_1(t_cube_struct *cube_struct)
{
	t_all		vars;
	t_render 	render;
	t_data 		img;

	render.mlx = NULL;
	render.mlx_win = NULL;
	render.win = NULL;
	img.img = NULL;
	img.addr = NULL;
	img.bits_per_pixel = 0;
	img.endian = 0;
	img.line_length = 0;
	vars.pars = cube_struct;
	vars.render = render;
	vars.img = img;
	return (vars);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void put_pers(t_all *vars)
{
	vars->locate->x = (vars->cnt->cnt_2 * vars->locate->eq) + vars->locate->eq/2;
	vars->locate->y = (vars->cnt->cnt_1 * vars->locate->eq) + vars->locate->eq/2;
    my_mlx_pixel_put(vars->img.img, vars->locate->x , vars->locate->y, 0x00ff0000);
    mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
}

static void put_pixel_map(t_all *vars)
{
	int	x;
	int	y;

	while (vars->cnt->cnt_4 <= vars->locate->eq)
    {
		y = (vars->cnt->cnt_1 * vars->locate->eq) + vars->cnt->cnt_4;

        while (vars->cnt->cnt_3 <= vars->locate->eq)
        {
			x = (vars->cnt->cnt_2 * vars->locate->eq) + vars->cnt->cnt_3;
            my_mlx_pixel_put(vars->img.img, x, y, vars->pars->flor_clr);
            mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
			vars->cnt->cnt_3++;
        }
		vars->cnt->cnt_4++;
		vars->cnt->cnt_3 = 0;
    }
	vars->cnt->cnt_4 = 0;
	vars->cnt->cnt_3 = 0;
}

static void render_map(t_all *vars)
{
	init_vars_2(vars);
    while(vars->pars->map[vars->cnt->cnt_1])
    {
        while(vars->pars->map[vars->cnt->cnt_1][vars->cnt->cnt_2])
        {
            if(vars->pars->map[vars->cnt->cnt_1][vars->cnt->cnt_2] == '1')
                put_pixel_map(vars);
            if(vars->pars->map[vars->cnt->cnt_1][vars->cnt->cnt_2] == 'N')
                put_pers(vars);
            vars->cnt->cnt_2++;
        }
        vars->cnt->cnt_2 = 0;
		vars->cnt->cnt_1++;
    }
}

int		move(int keycode, t_all *vars)
{
	if (keycode == 126)
	{
//		vars->locate.x -= vars->locate.eq;
//		vars->locate.x = (vars->cnt.cnt_2 * vars->locate.eq) + vars->locate.eq/2;
//		vars->locate.y = (vars->cnt.cnt_1 * vars->locate.eq) + vars->locate.eq/2;
		vars->locate->x++;
		put_pers(vars);
		render_map(vars);
	}
	return 1;
}

void		go_to_screen(t_cube_struct *cube_struct)
{
    t_all		vars;
    t_render 	render;

//	vars = malloc(sizeof(*vars));
	vars = init_vars_1(cube_struct);
	vars.render.mlx = mlx_init();
	vars.render.mlx_win = mlx_new_window(vars.render.mlx, vars.pars->res_x, vars.pars->res_y, "Hello world!");
	vars.img.img = mlx_new_image(vars.render.mlx, vars.pars->res_x, vars.pars->res_y);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);
//    init_vars_1(r_data, cube_struct, vars);
    render_map(&vars);
	mlx_hook(vars.render.mlx_win, 2, 0, move, &vars);
    mlx_loop(vars.render.mlx);
}
