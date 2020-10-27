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

//#include "parser.h"
#include "render.h"
#include <stdio.h>

// It will need to fix: finding angels of start for sprites which lockated on 0, M_PI/2, M_PI, 3*M_PI/2 and 2*M_PI
//


void	sprite_pos(t_all *vars, t_cnt *cnt, t_list **lst_copy)
{
	t_sprt	*sprt;

	sprt = malloc(sizeof(t_sprt));
//	sprt->x = (float)(vars->pars.map[cnt->cnt_1][cnt->cnt_2 - 1] == '1' ? cnt->cnt_2 + 1 : cnt->cnt_2 - 1);
//	sprt->y = (float)(vars->pars.map[cnt->cnt_1 - 1][cnt->cnt_2] == '1' ? cnt->cnt_1 + 1 : cnt->cnt_1 - 1);
	sprt->x = (float)(vars->pars.map[cnt->cnt_1][cnt->cnt_2 - 1] == '1' ? cnt->cnt_2 + 0.5 : cnt->cnt_2 - 0.5);
	sprt->y = (float)(vars->pars.map[cnt->cnt_1 - 1][cnt->cnt_2] == '1' ? cnt->cnt_1 + 0.5 : cnt->cnt_1 - 0.5);
	if(!vars->list_1)
	{
		*lst_copy = ft_lstnew(sprt);
		vars->list_1 = *lst_copy;
	}
	else
		ft_lstadd_back(&(*lst_copy), ft_lstnew(sprt));
	vars->sprt_num++;
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
		vars->locate.x += 0.2 * cosf(vars->k + vars->angle_r);
		vars->locate.y += 0.2 * sinf(vars->k + vars->angle_r);
	}
	if (keycode == 125 && vars->pars.map[(int)(vars->locate.y - 0.5 * sinf(vars->k + vars->angle_r))][(int)(vars->locate.x - 0.5 * cosf(vars->k + vars->angle_r))] != '1')
	{
		vars->locate.x -= 0.2 * cosf(vars->k + vars->angle_r);
		vars->locate.y -= 0.2 * sinf(vars->k + vars->angle_r);
	}
	if (keycode == 124 && vars->pars.map[(int)(vars->locate.y - 0.5 * sin(M_PI/k + vars->angle_r)*c)][(int)(vars->locate.x - 0.5 * cos(M_PI/k + vars->angle_r)*c)] != '1')
	{
		vars->locate.x -= 0.2 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y -= 0.2 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 123 && vars->pars.map[(int)(vars->locate.y + 0.5 * sin(M_PI/k + vars->angle_r)*c)][(int)(vars->locate.x + 0.5 * cos(M_PI/k + vars->angle_r)*c)] != '1')
	{
		vars->locate.x += 0.2 * cos(M_PI/k + vars->angle_r)*c;
		vars->locate.y += 0.2 * sin(M_PI/k + vars->angle_r)*c;
	}
	if (keycode == 0)
		vars->angle_r += 358*M_PI/180;
	if (keycode == 2)
		vars->angle_r += 2*M_PI/180;
	vector_vision(vars);
	return (1);
}

void	pers_position(t_all *vars, t_cube_struct *pars, t_cnt *cnt)
{
	t_list	*lst_copy;

	null_cnt(vars);
	while(pars->map[cnt->cnt_1])
	{
		while(pars->map[cnt->cnt_1][cnt->cnt_2])
		{
			if(pars->map[cnt->cnt_1][cnt->cnt_2] == 'N' && (vars->locate.x == 0 && vars->locate.y == 0))
			{
				vars->locate.v_vis = 'N';
				vars->locate.x = (float)(pars->map[cnt->cnt_1][cnt->cnt_2 - 1] == '1' ? cnt->cnt_2 + 1.01 : cnt->cnt_2 - 1.01);
				vars->locate.y = (float)(pars->map[cnt->cnt_1 - 1][cnt->cnt_2] == '1' ? cnt->cnt_1 + 1.01: cnt->cnt_1 - 1.01);
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
				vars->locate.y = (float)(pars->map[cnt->cnt_1 - 1][cnt->cnt_2] == '1' ? cnt->cnt_1 + 0.4 : cnt->cnt_1 - 0.4);
			}
			if(pars->map[cnt->cnt_1][cnt->cnt_2] == '2')
				sprite_pos(vars, &vars->cnt, &lst_copy);
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