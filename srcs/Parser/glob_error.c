/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:17:03 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 15:17:10 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int		otshib_ochka_x(t_cube *cub_st)
{
	int	i;

	i = 0;
	while (cub_st->path[i])
	{
		free(cub_st->path[i]);
		cub_st->path[i] = NULL;
		i++;
	}
	exit(0);
}

void	otshib_ochka(t_cube *cub_st, int errno)
{
	if (errno != -1)
	{
		cub_st->mp = ft_strdup("invalid map format.\n+invalid map-file.\n"
					"+wrong resolution params.\n+invalid floor/ceilling colour."
						"\n+invalid path to texture.\n+invalid texture format."
		"\n+invalid number of params.\n+expected colour/ceilling or floor.\n"
													"+invalid argument.\n");
		cub_st->tmp = ft_split(cub_st->mp, '+');
		ft_putstr_fd(ft_strjoin("Error\n", cub_st->tmp[errno]), 1);
		exit(errno);
	}
	exit(0);
}
