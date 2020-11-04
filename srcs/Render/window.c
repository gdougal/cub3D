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

#include "render.h"

void		txtrs_init(t_all *vars)
{
	int i;

	i = 0;
	while (vars->pars.path[i])
	{
		if (!(vars->txtrs[i].img = mlx_xpm_file_to_image(&vars->render.mlx,
			vars->pars.path[i], &vars->txtrs[i].width, &vars->txtrs[i].height)))
			otshib_ochka(&vars->pars, 6);
		vars->txtrs[i].adr = mlx_get_data_addr(vars->txtrs[i].img,
			&vars->txtrs[i].bits_per_pix, &vars->txtrs[i].line_length,
												&vars->txtrs[i].endian);
		i++;
	}
	vars->txtrs[i].img = NULL;
	vars->txtrs[i].adr = NULL;
}

void		go_to_screen(t_cube *cube_struct)
{
	t_all	vars;

	vars = init_vars(cube_struct);
	vars.render.mlx = mlx_init();
	vars.render.mlx_win = mlx_new_window(vars.render.mlx,
		(int)vars.pars.res_x, (int)vars.pars.res_y, "Hello world!");
	vars.img.img = mlx_new_image(vars.render.mlx,
		(int)vars.pars.res_x, (int)vars.pars.res_y);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	pers_position(&vars, &vars.pars, &vars.cnt);
	txtrs_init(&vars);
	vector_vision(&vars);
	if (vars.pars.save == 1)
		screenshoot(&vars);
	mlx_hook(vars.render.mlx_win, 2, 0, move, &vars);
	mlx_hook(vars.render.mlx_win, 17, 17, otshib_ochka_x, cube_struct);
	mlx_loop(vars.render.mlx);
}
