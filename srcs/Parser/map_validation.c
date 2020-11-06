/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:31:49 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 18:31:51 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		map_validation_x(t_cube *cub_st, int i, int j)
{
	int	x;
	int	y;

	y = i;
	x = j;
	while (x < (int)cub_st->height && cub_st->map[x][y] != '1')
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			otshib_ochka(cub_st, 0);
		x++;
	}
	x = j;
	while (x > 0 && cub_st->map[x][y] != '1')
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			otshib_ochka(cub_st, 0);
		x--;
	}
}

static void		map_validation_y(t_cube *cub_st, int i, int j)
{
	int	x;
	int	y;

	y = i;
	x = j;
	if (i == 0 || j == 0 || j == (int)cub_st->height - 1 ||
			i == (int)cub_st->width - 1)
		otshib_ochka(cub_st, 0);
	while (y < (int)cub_st->width && cub_st->map[x][y] != '1')
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			otshib_ochka(cub_st, 0);
		y++;
	}
	y = i;
	while (y > 0 && cub_st->map[x][y] != '1')
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			otshib_ochka(cub_st, 0);
		y--;
	}
	map_validation_x(cub_st, i, j);
}

void			map_val(t_cube *cub_st)
{
	int	i;
	int	j;

	j = 0;
	while (cub_st->map[j])
	{
		while (cub_st->map[j][i] != '\0')
		{
			if (cub_st->map[j][i] == '0' || cub_st->map[j][i] == 'N' ||
				cub_st->map[j][i] == 'S' || cub_st->map[j][i] == 'W' ||
				cub_st->map[j][i] == 'E' || cub_st->map[j][i] == '2')
				map_validation_y(cub_st, i, j);
			i++;
		}
		i = 0;
		j++;
	}
}

void			valid_sym_map(char *tmp, t_cube *cub_st)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (!ft_strchr("012NEWS ", tmp[i]))
			otshib_ochka(cub_st, 0);
		if (ft_strchr("NEWS", tmp[i]))
			cub_st->player++;
		i++;
	}
	if (i == 0)
		otshib_ochka(cub_st, 0);
}
