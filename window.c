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
#include <stdio.h>


void	null_cnt(t_all *vars)
{
	vars->cnt.cnt_1 = 0;
	vars->cnt.cnt_2 = 0;
}


void	my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color)
{
	char    *dst;

	dst = vars->img.addr + (y * vars->img.line_length + x * (vars->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
		vars->k = 3*M_PI/2;
	if (vars->locate.v_vis == 'W')
		vars->k = M_PI;
	if (vars->locate.v_vis == 'S')
		vars->k = 3*M_PI/2;
	if (vars->locate.v_vis == 'E')
		vars->k = 0;
}

void vector_vision(t_all *vars)
{
	double	fov;
	double	fov_2;
	double	x;
	double	y;
	double	x_1;
	double	y_1;

	double	step;
	double	step_1;
	double	delta_x;
	double	delta_y;
	int bool  = 0;

	fov = (vars->fov*M_PI)/180;
	fov_2 = (vars->fov*M_PI)/360;
	null_cnt(vars);
	popravka(vars);
	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
	while(fov >= fov_2)
	{
		vars->dist = 0;
		step = 0;
		step_1 = 0;
		if (cos(vars->angle_s - fov) >= 0)
			x_1 = floor(vars->locate.x);
		else
			x_1 = ceil(vars->locate.x);

		if (sin(vars->angle_s - fov) < 0)
			y_1 = floor(vars->locate.y);
		else
			y_1 = ceil(vars->locate.y);
		while(1)
		{
			if (cos(vars->angle_s - fov) >= 0)
			{
				delta_x = vars->locate.x - x_1 - step;
				x = x_1 - step;
				delta_y = delta_x / tan(vars->angle_s - fov);
				y = vars->locate.y + delta_y;
			}
			else
			{
				delta_x = x_1 - vars->locate.x + step;
				x = x_1 + step;
				delta_y = delta_x / tan(vars->angle_s - fov);
				y = vars->locate.y + delta_y;
			}
			if (x >= 0 && y >= 0 && y < vars->pars.height && vars->pars.map[(int) floor(y)][(int)(x)] == '1')
			{
				vars->dist = sqrt(delta_x*delta_x + delta_y*delta_y);
				vars->cnt.cnt_2 = 0;
				wall_calc(vars);
				vars->cnt.cnt_1++;
				break;
			}
			++step;
//			if(vars->pars.map[(int) floor(y)][(int)(x)] != '1')
//			{
//				if (sin(vars->angle_s - fov) < 0)
//				{
//					delta_y = vars->locate.y - y_1 - step_1;
//					y = y_1 - step_1;
//					delta_x = delta_y * tan(vars->angle_s - fov);
//					x = vars->locate.x + delta_x;
//				}
//				else
//				{
//					delta_y = y_1 - vars->locate.y + step_1;
//					y = y_1 + step_1;
//					delta_x = delta_y  * tan(vars->angle_s - fov);
//					x = vars->locate.x + delta_x;
//				}
//				if (x >= 0 && y >= 0 && x <= vars->pars.width && vars->pars.map[(int) floor(y)][(int) floor(x)] == '1')
//				{
//					vars->dist = sqrt(delta_x*delta_x + delta_y*delta_y);
//					vars->cnt.cnt_2 = 0;
//					wall_calc(vars);
//					vars->cnt.cnt_1++;
//					break;
//				}
//				step_1++;
//			}
		}
		fov -= ((vars->fov/(vars->pars.res_x))*M_PI)/180;
	}
	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
}


//if ((sin(fov) >= sin((45*M_PI)/180) && sin(fov) <= sin((135*M_PI)/180)) || (sin(fov) >= sin((225*M_PI)/180) && sin(fov) <= sin((315*M_PI)/180)))
//side = 1;


//void vector_vision(t_all *vars)
//{
//	double	fov;
//	double	fov_2;
//	double	fov_stp = ((vars->fov/(vars->pars.res_x))*M_PI)/180;
//	double	x;
//	double	y;
//
//	double	stp;
//	int		side;
//
//	fov = (vars->fov*M_PI)/180;
//	fov_2 = (vars->fov*M_PI)/360;
//	null_cnt(vars);
//	popravka(vars);
//	vars->cnt.cnt_1 = (int)vars->pars.res_x;
//	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
//	while(fov >= 0)
//	{
////		side = 0;
//		stp = 0;
////		if ((sin(fov) >= sin((45*M_PI)/180) && sin(fov) <= sin((135*M_PI)/180)) || (sin(fov) >= sin((225*M_PI)/180) && sin(fov) <= sin((315*M_PI)/180)))
////			side = 1;
//		while(1)
//		{
//			x = vars->locate.x + stp*cos(vars->angle_s - fov);
//			y = vars->locate.y + stp*sin(vars->angle_s - fov);
//			if (vars->pars.map[(int) floor(y)][(int) floor(x)] == '1')
//			{
//				vars->dist = stp;
//				vars->cnt.cnt_2 = 0;
//				wall_calc(vars);
//				vars->cnt.cnt_1--;
//				break;
//			}
//			stp += 0.001;
//		}
//		fov -= fov_stp;
//		if (cos(vars->angle_s - fov))
//			printf("%lf\n", (sin(vars->angle_s - fov)));
//	}
//	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
//}

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
			vars->locate.x += 0.1 * cos(vars->k + vars->angle_r);
			vars->locate.y += 0.1 * sin(vars->k + vars->angle_r);
	}
	if (keycode == 125 && vars->pars.map[(int)(vars->locate.y + 0.3 * sin(M_PI/2 + vars->angle_r))][(int)(vars->locate.x + 0.3 * cos(M_PI/2 + vars->angle_r))] != '1')
	{
			vars->locate.x -= 0.1 * cos(vars->k + vars->angle_r);
			vars->locate.y -= 0.1 * sin(vars->k + vars->angle_r);
	}
	if (keycode == 124 && vars->pars.map[(int)(vars->locate.y + 0.3 * sin(M_PI + vars->angle_r))][(int)(vars->locate.x + 0.3 * cos(M_PI + vars->angle_r))] != '1')
	{
		vars->locate.x -= 0.1 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y -= 0.1 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 123 && vars->pars.map[(int)(vars->locate.y - 0.3 * sin(M_PI + vars->angle_r))][(int)(vars->locate.x - 0.3 * cos(M_PI + vars->angle_r))] != '1')
	{
		vars->locate.x += 0.1 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y += 0.1 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 0)
		vars->angle_r -= 3*M_PI/180;
	if (keycode == 2)
		vars->angle_r += 3*M_PI/180;
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
    free(vars.pars.map);
	free(vars.pars.path_s);
	free(vars.pars.path_sprite);
	free(vars.pars.path_n);
	free(vars.pars.path_e);
	free(vars.pars.path_w);
}
