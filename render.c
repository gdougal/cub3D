/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:44:11 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/12 12:44:13 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "struct.h"

void	my_mlx_pixel_put(t_all *vars, int x, int y, unsigned int color)
{
	char    *dst;

	dst = vars->img.addr + (y * vars->img.line_length + x * (vars->img.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


//void put_pers(t_all *vars)
//{
//	my_mlx_pixel_put(vars, vars->locate.x, vars->locate.y, 0x00ff0000);
//	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
//}

//static void put_pixel_map(t_all *vars)
//{
//	int	x;
//	int	y;
//	y = vars->cnt.cnt_1;
//	x = vars->cnt.cnt_2;
//	my_mlx_pixel_put(vars, x, y, vars->pars.flor_clr);
//	mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
//
//}

// НЕНУЖНАЯ ФУНКЦИЯ

//void render_flour(t_all *vars)
//{
//	vars->cnt.cnt_2 = 0;
//	vars->cnt.cnt_1 = 0;
//	while(vars->pars.map[vars->cnt.cnt_1])
//	{
//		while(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2])
//		{
//			if(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == '0' || vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'N')
//			{
//				my_mlx_pixel_put(vars, vars->cnt.cnt_2, vars->cnt.cnt_1, 0x0000000);
//				mlx_put_image_to_window(vars->render.mlx, vars->render.mlx_win, vars->img.img, 0, 0);
//			}
//			vars->cnt.cnt_2++;
//		}
//		vars->cnt.cnt_2 = 0;
//		vars->cnt.cnt_1++;
//	}
//}
// НЕНУЖНАЯ ФУНКЦИЯ
//


//void render_map(t_all *vars)
//{
//	vars->cnt.cnt_2 = 0;
//	vars->cnt.cnt_1 = 0;
//	while(vars->pars.map[vars->cnt.cnt_1])
//	{
//		while(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2])
//		{
//			if(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == '1')
//				put_pixel_map(vars);
//			if(vars->pars.map[vars->cnt.cnt_1][vars->cnt.cnt_2] == 'N' && (vars->locate.x == 0 && vars->locate.y == 0))
//			{
//				vars->locate.v_vis = 'N';
//				vars->locate.x = vars->cnt.cnt_2;
//				vars->locate.y = vars->cnt.cnt_1;
//				put_pers(vars);
//			}
//			vars->cnt.cnt_2++;
//		}
//		vars->cnt.cnt_2 = 0;
//		vars->cnt.cnt_1++;
//	}
//}

