/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor_R_F_C.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:23:55 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 15:24:07 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	resol_pars(t_cube *cub_st, char **tmp, int j)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		otshib_ochka(cub_st, 2);
	i = 0;
	while (tmp[j][i])
		if (!(ft_isdigit(tmp[j][i++])))
			otshib_ochka(cub_st, 2);
	if (j == 1 && i < 5)
		cub_st->res_x = (float)ft_atoi(tmp[j]);
	if ((j == 1 && i >= 5) || (cub_st->res_x > 2560))
		cub_st->res_x = 2560;
	if (j == 2 && i < 5)
		cub_st->res_y = (float)ft_atoi(tmp[2]);
	if ((j == 2 && i >= 5) || cub_st->res_y > 1440)
		cub_st->res_y = 1440;
	if (cub_st->res_x == 0 || cub_st->res_y == 0)
		otshib_ochka(cub_st, 2);
}

static void	colour_pars(t_cube *cub_st, int k)
{
	int r;
	int g;
	int b;

	color_check(cub_st);
	r = ft_atoi(cub_st->tmp[0]);
	g = ft_atoi(cub_st->tmp[1]);
	b = ft_atoi(cub_st->tmp[2]);
	if (k == 1 && r <= 255 && g <= 255 && b <= 255)
		cub_st->flor_clr = (unsigned int)create_trgb(0, r, g, b);
	else if (k == 2 && r <= 255 && g <= 255 && b <= 255)
		cub_st->ceilling_clr = (unsigned int)create_trgb(0, r, g, b);
	else
		otshib_ochka(cub_st, 3);
}

static void	proc_resol(t_cube *cub_st, char *line)
{
	cub_st->tmp = ft_split(line, ' ');
	resol_pars(cub_st, cub_st->tmp, 1);
	resol_pars(cub_st, cub_st->tmp, 2);
	cub_st->lines++;
}

static void	proc_colour(t_cube *cub_st, char *line, char l)
{
	int		i;
	int		j;

	cub_st->mp = NULL;
	i = 0;
	j = 0;
	cub_st->mp = ft_strtrim(line, "CF ");
	while (cub_st->mp[i])
		if (cub_st->mp[i++] == ',')
			j++;
	if (j >= 3)
		otshib_ochka(cub_st, 3);
	cub_st->tmp = ft_split(cub_st->mp, ',');
	if (l == 'F')
		colour_pars(cub_st, 1);
	else if (l == 'C')
		colour_pars(cub_st, 2);
	cub_st->lines++;
	if (cub_st->mp)
		free(cub_st->mp);
}

void		proc_numbers(char *line, char l, t_cube *cub_st)
{
	int	i;

	if (l == 'R' || l == 'F' || l == 'C')
	{
		if (l == 'R')
			proc_resol(cub_st, line);
		else
			proc_colour(cub_st, line, l);
		i = 0;
		while (cub_st->tmp[i])
			free(cub_st->tmp[i++]);
		free(cub_st->tmp);
	}
}
