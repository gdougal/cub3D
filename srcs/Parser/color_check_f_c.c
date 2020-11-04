/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check_F_C.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:10:29 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 17:10:34 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_check(t_cube *cub_st)
{
	int j;
	int	i;

	j = 0;
	while (cub_st->tmp[j])
		j++;
	if (j == 3)
	{
		j = 0;
		while (cub_st->tmp[j])
		{
			i = 0;
			while (cub_st->tmp[j][i])
				if (!(ft_isdigit(cub_st->tmp[j][i++])))
					otshib_ochka(cub_st, 3);
			j++;
		}
	}
	else
		otshib_ochka(cub_st, 3);
}
