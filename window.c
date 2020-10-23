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


void	what_a_side(t_all *vars, double dst_x, double dst_y, double fov)
{
	if(dst_x < dst_y && cos(vars->angle_s - fov) < 0)
		vars->hit = 1;
	else if(dst_x < dst_y && cos(vars->angle_s - fov) > 0)
		vars->hit = 2;
	else if(dst_y < dst_x && sin(vars->angle_s - fov) < 0)
		vars->hit = 3;
	else if(dst_y < dst_x && sin(vars->angle_s - fov) > 0)
		vars->hit = 4;
}


float	dist_x(t_all *vars, float fov)
{
	int 	k = 0;
	int		hit = 0;

		while(!hit)
		{
			vars->d_x = fabsf(vars->locate.x - (vars->x_fc + k));
			if ((vars->angle_s - fov) > M_PI/2 && (vars->angle_s - fov) < 3*M_PI/2)
			{
				vars->d_y = vars->d_x * ((-1) * tanf(vars->angle_s - fov));
				vars->x_1 = vars->locate.x - vars->d_x;
				k -= 1;
			}
			else
			{
				vars->d_y = vars->d_x * (tanf(vars->angle_s - fov));
				vars->x_1 = vars->locate.x + vars->d_x;
				k += 1;
			}
			vars->y_1 = vars->locate.y + (vars->d_y);
			if (vars->y_1 <= 0 || vars->y_1 >= vars->pars.height || vars->x_1 >= vars->pars.width)
				break;
			if (cosf(vars->angle_s - fov) < 0 && vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1 - 1)] == '1')
				hit  = 1;
			else if (cosf(vars->angle_s - fov) >= 0 && vars->pars.map[(int)(vars->y_1)][(int)(vars->x_1)] == '1')
				hit  = 2;
		}
	return (sqrtf((vars->x_1 - vars->locate.x)*(vars->x_1 - vars->locate.x) + (vars->y_1 - vars->locate.y)*(vars->y_1 - vars->locate.y)));
}

float	dist_y(t_all *vars, float fov)
{
	int 	k = 0;
	int		hit = 0;

		while(!hit)
		{
			vars->d_y = fabsf(vars->locate.y - (vars->y_fc + k));
			if ((vars->angle_s - fov) > M_PI && (vars->angle_s - fov) < 2*M_PI)
			{
				vars->d_x = vars->d_y * ((-1) * 1 / tanf(vars->angle_s - fov));
				vars->y_2 = vars->locate.y - fabsf(vars->d_y);
				k -= 1;
			}
			else
			{
				vars->d_x = vars->d_y * (1 / tanf(vars->angle_s - fov));
				vars->y_2 = vars->locate.y + fabsf(vars->d_y);
				k += 1;
			}
			vars->x_2 = vars->locate.x + (vars->d_x);
			if (vars->x_2 <= 0 || vars->x_2 >= vars->pars.width ||  vars->y_2 >= vars->pars.height)
				break;
			if (sinf(vars->angle_s - fov) < 0 && vars->pars.map[(int)(vars->y_2 - 1)][(int)(vars->x_2)] == '1')
				hit = 3;
			else if(sinf(vars->angle_s - fov) >= 0 && vars->pars.map[(int)(vars->y_2)][(int)(vars->x_2)] == '1')
				hit = 4;
	}
	return (sqrtf((vars->x_2 - vars->locate.x)*(vars->x_2 - vars->locate.x) + (vars->y_2 - vars->locate.y)*(vars->y_2 - vars->locate.y)));
}

void	calc_del_x_y(t_all *vars, double fov)
{
	if ((vars->angle_s - fov) > M_PI/2 && (vars->angle_s - fov) < 3*M_PI/2)
		vars->x_fc = floorf(vars->locate.x);
	else
		vars->x_fc = ceilf(vars->locate.x);

	if ((vars->angle_s - fov) > M_PI && (vars->angle_s - fov) < 2*M_PI)
		vars->y_fc = floorf(vars->locate.y);
	else
		vars->y_fc = ceilf(vars->locate.y);
}

void	vector_vision(t_all *vars)
{
	float	fov = vars->fov;
	float	fov_2 = fov/2;
	float	fov_stp = fov/vars->pars.res_x;
	float	dst_x;
	float	dst_y;

	null_cnt(vars);
	popravka(vars);
	vars->angle_s = (vars->k + fov_2 + vars->angle_r);
	while((vars->angle_s - fov) > 2*M_PI)
		vars->angle_s -= 2*M_PI;
	while (fov >= 0)
	{
		vars->dist = 0;
		calc_del_x_y(vars, fov);
		dst_x = dist_x(vars, fov);
		dst_y = dist_y(vars, fov);
		what_a_side(vars, dst_x, dst_y, fov);
		vars->dist = (dst_x  <= dst_y ? dst_x : dst_y) * cosf((vars->angle_s - fov) - (vars->k + vars->angle_r));

		wall_calc(vars);
		vars->cnt.cnt_1++;
		fov -= fov_stp;
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
	if (keycode == 126 && vars->pars.map[(int)(vars->locate.y + 0.5 * sinf(vars->k + vars->angle_r))][(int)(vars->locate.x + 0.5 * cosf(vars->k + vars->angle_r))] != '1')
	{
			vars->locate.x += 0.3 * cosf(vars->k + vars->angle_r);
			vars->locate.y += 0.3 * sinf(vars->k + vars->angle_r);
	}
	if (keycode == 125 && vars->pars.map[(int)(vars->locate.y - 0.5 * sinf(vars->k + vars->angle_r))][(int)(vars->locate.x - 0.5 * cosf(vars->k + vars->angle_r))] != '1')
	{
			vars->locate.x -= 0.3 * cosf(vars->k + vars->angle_r);
			vars->locate.y -= 0.3 * sinf(vars->k + vars->angle_r);
	}
	if (keycode == 124 && vars->pars.map[(int)(vars->locate.y - 0.5 * sin(M_PI/k + vars->angle_r)*c)][(int)(vars->locate.x - 0.5 * cos(M_PI/k + vars->angle_r)*c)] != '1')
	{
		vars->locate.x -= 0.3 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y -= 0.3 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 123 && vars->pars.map[(int)(vars->locate.y + 0.5 * sin(M_PI/k + vars->angle_r)*c)][(int)(vars->locate.x + 0.5 * cos(M_PI/k + vars->angle_r)*c)] != '1')
	{
		vars->locate.x += 0.3 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y += 0.3 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 0)
		vars->angle_r += 356*M_PI/180;
	if (keycode == 2)
		vars->angle_r += 4*M_PI/180;
	vector_vision(vars);
	return (1);
}



void	sprite_pos(t_all *vars, t_cnt *cnt)
{

	vars->sprt.x_sprt = cnt->cnt_2;
	vars->sprt.y_sprt = cnt->cnt_1;
	if(!vars->sprt_num)
		vars->list_1 = *ft_lstnew(&vars->sprt);
	else
		ft_lstadd_back(&vars->list_1.next, ft_lstnew(&vars->sprt));
	vars->sprt_num++;
}


void	pers_position(t_all *vars, t_cube_struct *pars, t_cnt *cnt)
{
	null_cnt(vars);
	while(pars->map[cnt->cnt_1])
	{
		while(pars->map[cnt->cnt_1][cnt->cnt_2])
		{
			if(pars->map[cnt->cnt_1][cnt->cnt_2] == 'N' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'N';
				vars->locate.x = (float)(pars->map[cnt->cnt_1][cnt->cnt_2 - 1] == '1' ? cnt->cnt_2 + 1.01 : cnt->cnt_2 - 1.01);
				vars->locate.y = (float)(pars->map[cnt->cnt_1 - 1][cnt->cnt_2] == '1' ? cnt->cnt_1 + 1.01 : cnt->cnt_1 - 1.01);
			}
			else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'W' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'W';
				vars->locate.x = cnt->cnt_2;
				vars->locate.y = cnt->cnt_1;
			}
			else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'S' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'S';
				vars->locate.x = cnt->cnt_2;
				vars->locate.y = cnt->cnt_1;
			}
			else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'E' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'E';
				vars->locate.x = cnt->cnt_2;
				vars->locate.y = cnt->cnt_1;
			}
			if(pars->map[cnt->cnt_1][cnt->cnt_2] == '2')
				sprite_pos(vars, &vars->cnt);
			cnt->cnt_2++;
		}
		cnt->cnt_2 = 0;
		cnt->cnt_1++;
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
	pers_position(&vars, &vars.pars, &vars.cnt);
	vector_vision(&vars);
	mlx_hook(vars.render.mlx_win, 2, 0, move, &vars);
    mlx_loop(vars.render.mlx);
}
