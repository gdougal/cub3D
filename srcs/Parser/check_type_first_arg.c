/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_first_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:13:36 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 15:13:48 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		chek_type_first_arg(char *arg, t_cube *cub_st)
{
	int i;

	i = 0;
	if (arg)
	{
		while (arg[i])
			i++;
		if (ft_memcmp((arg + (i - 4)), ".cub", 4))
			otshib_ochka(cub_st, 0);
	}
	else
		otshib_ochka(cub_st, 0);
}
