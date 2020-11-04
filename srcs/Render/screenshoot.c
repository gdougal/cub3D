/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshoot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:22:17 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/03 11:22:19 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static unsigned int	pix_color(t_all *vars, int x, int y)
{
	char			*dst;
	unsigned int	color;

	dst = vars->img.addr + (y * vars->img.line_length
			+ x * (vars->img.bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

static void			blahblah(t_all *vars, unsigned char
		*bmpfilhdr, unsigned char *bmpinf, unsigned char *bmppad)
{
	int				fd;
	unsigned int	colour;

	fd = open("screenshoot.bmp", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0666);
	write(fd, bmpfilhdr, 14);
	write(fd, bmpinf, 40);
	vars->cnt.cnt_1 = vars->pars.res_y - 1;
	while (vars->cnt.cnt_1 >= 0)
	{
		vars->cnt.cnt_2 = 0;
		while (vars->cnt.cnt_2 < (int)vars->pars.res_x)
		{
			colour = pix_color(vars, vars->cnt.cnt_2, vars->cnt.cnt_1);
			write(fd, &colour, 3);
			vars->cnt.cnt_2++;
		}
		write(fd, bmppad, (4 - ((int)vars->pars.res_x * 3) % 4) % 4);
		vars->cnt.cnt_1--;
	}
	close(fd);
}

void				screenshoot(t_all *vars)
{
	unsigned int			filesize;
	static	unsigned char	bmpfilhdr[14] = {'B', 'M', 0, 0, 0, 0,
						0, 0, 0, 0, 54, 0, 0, 0};
	static	unsigned char	bmpinf[40] = {40, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 1, 0, 24, 0};
	static	unsigned char	bmppad[3] = {0, 0, 0};

	filesize = (unsigned int)(54 + 3 * vars->pars.res_x * vars->pars.res_y);
	bmpfilhdr[2] = (unsigned char)(filesize);
	bmpfilhdr[3] = (unsigned char)(filesize >> 8);
	bmpfilhdr[4] = (unsigned char)(filesize >> 16);
	bmpfilhdr[5] = (unsigned char)(filesize >> 24);
	bmpinf[4] = (unsigned char)((int)vars->pars.res_x);
	bmpinf[5] = (unsigned char)((int)vars->pars.res_x >> 8);
	bmpinf[6] = (unsigned char)((int)vars->pars.res_x >> 16);
	bmpinf[7] = (unsigned char)((int)vars->pars.res_x >> 24);
	bmpinf[8] = (unsigned char)((int)vars->pars.res_y);
	bmpinf[9] = (unsigned char)((int)vars->pars.res_y >> 8);
	bmpinf[10] = (unsigned char)((int)vars->pars.res_y >> 16);
	bmpinf[11] = (unsigned char)((int)vars->pars.res_y >> 24);
	blahblah(vars, bmpfilhdr, bmpinf, bmppad);
	otshib_ochka(&vars->pars, -1);
}
