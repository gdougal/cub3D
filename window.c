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
	vars->cnt.cnt_1 = 0;
	vars->cnt.cnt_2 = 0;
}


void render_cub(t_all *vars)
{
	while(vars->cnt.cnt_2 < vars->w_s)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->pars.ceilling_clr);
		vars->cnt.cnt_2++;
	}
	while(vars->cnt.cnt_2 >= vars->w_s && vars->cnt.cnt_2 <= vars->w_e)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->w_color);
		vars->cnt.cnt_2++;
	}
	while(vars->cnt.cnt_2 > vars->w_e && vars->cnt.cnt_2 < vars->pars.res_y - 1)
	{
		my_mlx_pixel_put(vars, vars->cnt.cnt_1, vars->cnt.cnt_2, vars->pars.flor_clr);
		vars->cnt.cnt_2++;
	}
}

void wall_calc(t_all *vars)
{
	vars->h_wll = vars->pars.res_y/vars->dist;
	vars->w_s = (vars->pars.res_y - vars->h_wll)/2;
	vars->w_e = vars->w_s + vars->h_wll;
	render_cub(vars);
}

void popravka(t_all *vars)
{
	if (vars->locate.v_vis == 'N')
		vars->k = -M_PI/2;
	if (vars->locate.v_vis == 'W')
		vars->k = M_PI;
	if (vars->locate.v_vis == 'S')
		vars->k = M_PI/2;
	if (vars->locate.v_vis == 'E')
		vars->k = 0;
}

void vector_vision(t_all *vars)
{
	double	fov;
	double	fov_2;
	double	x;
	double	y;

	fov = (vars->fov*M_PI)/180;
	fov_2 = (vars->fov*M_PI)/360;
	vars->r_fov = fov;
	null_cnt(vars);
	popravka(vars);
	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
	while(fov >= 0)
	{
		vars->dist = 0;
		while(1)
		{
			x = vars->locate.x + vars->dist*cos(vars->angle_s - fov);
			y = vars->locate.y + vars->dist*sin(vars->angle_s - fov);
			if (vars->pars.map[(int) floor(y)][(int) floor(x)] == '1')
			{
				vars->cnt.cnt_2 = 0;
				wall_calc(vars);
				vars->cnt.cnt_1++;
				break;
			}
			vars->dist += 0.001;
		}
		fov -= ((vars->fov/(vars->pars.res_x))*M_PI)/180;
	}
	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
}

int		move(int keycode, t_all *vars)
{
	int	c;
	int k;

	c = 1;
	k = 1;
	if (vars->locate.v_vis == 'S' || vars->locate.v_vis == 'E')
		c = -1;
	if (vars->locate.v_vis == 'W' || vars->locate.v_vis == 'E')
		k = 2;
	if (keycode == 126 && vars->pars.map[(int)(vars->locate.y - 0.3 * sin(M_PI/2 + vars->angle_r))][(int)(vars->locate.x - 0.3 * cos(M_PI/2 + vars->angle_r))] != '1')
	{
			vars->locate.x += 0.15 * cos(vars->k + vars->angle_r);
			vars->locate.y += 0.15 * sin(vars->k + vars->angle_r);
	}
	if (keycode == 125 && vars->pars.map[(int)(vars->locate.y + 0.3 * sin(M_PI/2 + vars->angle_r))][(int)(vars->locate.x + 0.3 * cos(M_PI/2 + vars->angle_r))] != '1')
	{
			vars->locate.x -= 0.15 * cos(vars->k + vars->angle_r);
			vars->locate.y -= 0.15 * sin(vars->k + vars->angle_r);
	}
	if (keycode == 124 && vars->pars.map[(int)(vars->locate.y + 0.3 * sin(M_PI + vars->angle_r))][(int)(vars->locate.x + 0.3 * cos(M_PI + vars->angle_r))] != '1')
	{
		vars->locate.x -= 0.15 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y -= 0.15 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 123 && vars->pars.map[(int)(vars->locate.y - 0.3 * sin(M_PI + vars->angle_r))][(int)(vars->locate.x - 0.3 * cos(M_PI + vars->angle_r))] != '1')
	{
		vars->locate.x += 0.15 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y += 0.15 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 0)
		vars->angle_r -= 4*M_PI/180;
	if (keycode == 2)
		vars->angle_r += 4*M_PI/180;
	vector_vision(vars);
	return (1);
}

void	pers_position(t_all *vars)
{
	null_cnt(vars);
	while(vars->pars.map[vars->cnt.cnt_1])
	{
		while(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2])
		{
			if(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'N' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'N';
				vars->locate.x = vars->cnt.cnt_2;
				vars->locate.y = vars->cnt.cnt_1;
			}
			else if (vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'W' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'W';
				vars->locate.x = vars->cnt.cnt_2;
				vars->locate.y = vars->cnt.cnt_1;
			}
			else if (vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'S' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'S';
				vars->locate.x = vars->cnt.cnt_2;
				vars->locate.y = vars->cnt.cnt_1;
			}
			else if (vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'E' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'E';
				vars->locate.x = vars->cnt.cnt_2;
				vars->locate.y = vars->cnt.cnt_1;
			}
			vars->cnt.cnt_2++;
		}
		vars->cnt.cnt_2 = 0;
		vars->cnt.cnt_1++;
	}
	null_cnt(vars);
}

void		go_to_screen(t_cube_struct *cube_struct)
{
    t_all		vars;

	vars = init_vars(cube_struct);
	vars.render.mlx = mlx_init();
	vars.render.mlx_win = mlx_new_window(vars.render.mlx, (int)vars.pars.res_x, (int)vars.pars.res_y, "Hello world!");
	vars.img.img = mlx_new_image(vars.render.mlx, (int)vars.pars.res_x, (int)vars.pars.res_y);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
                                 &vars.img.endian);
	pers_position(&vars);
	vector_vision(&vars);
	mlx_hook(vars.render.mlx_win, 2, 0, move, &vars);
    mlx_loop(vars.render.mlx);
}
