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
#include "render.h"


void	null_cnt(t_all *vars)
{
	vars->cnt.cnt_3 = 0;
	vars->cnt.cnt_4 = 0;
	vars->cnt.cnt_1 = 0;
	vars->cnt.cnt_2 = 0;
}

int		move(int keycode, t_all *vars)
{
	if (keycode == 126)
	{
		vars->locate.y--;
		null_cnt(vars);
		render_map(vars);
		put_pers(vars);
	}
	else if (keycode == 125)
	{
		vars->locate.y++;
		null_cnt(vars);
		render_map(vars);
		put_pers(vars);
	}
	else if (keycode == 124)
	{
		vars->locate.x++;
		null_cnt(vars);
		render_map(vars);
		put_pers(vars);
	}
	else if (keycode == 123)
	{
		vars->locate.x--;
		null_cnt(vars);
		render_map(vars);
		put_pers(vars);
	}

	return 1;
}

void		go_to_screen(t_cube_struct *cube_struct)
{
    t_all		vars;

	vars = init_vars(cube_struct);
	vars.render.mlx = mlx_init();
	vars.render.mlx_win = mlx_new_window(vars.render.mlx, vars.pars.res_x, vars.pars.res_y, "Hello world!");
	vars.img.img = mlx_new_image(vars.render.mlx, vars.pars.res_x, vars.pars.res_y);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);
    render_map(&vars);
	mlx_hook(vars.render.mlx_win, 2, 0, move, &vars);
    mlx_loop(vars.render.mlx);
}
