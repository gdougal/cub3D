/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:05:10 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/04 19:25:35 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	first_part_params(char *line, t_cube *cub_st, int *i)
{
	(*i) = 0;
	if (line[0] == 'R' && cub_st->res_y == -1 && cub_st->res_x == -1)
		proc_numbers(line, 'R', cub_st);
	else if (line[0] == 'R' && cub_st->res_y != -1 && cub_st->res_x != -1)
		otshib_ochka(cub_st, 0);
	else if (line[0] == 'F')
		proc_numbers(line, 'F', cub_st);
	else if (line[0] == 'C')
		proc_numbers(line, 'C', cub_st);
	else if (!ft_memcmp(line, "NO", 2))
		proc_path(line, 'N', cub_st);
	else if (!ft_memcmp(line, "SO", 2))
		proc_path(line, 'S', cub_st);
	else if (!ft_memcmp(line, "WE", 2))
		proc_path(line, 'W', cub_st);
	else if (!ft_memcmp(line, "EA", 2))
		proc_path(line, 'E', cub_st);
	else if (line[0] == 'S')
		proc_path(line, 's', cub_st);
	else if (cub_st->lines == 8)
		while (line[*i])
			if (!(ft_strchr("NEWS 021", line[(*i)++])))
				otshib_ochka(cub_st, 0);
	free(line);
}

static void	check_argc(int argc, char **argv, t_cube *cub_st)
{
	int	i;

	i = 0;
	if (argc != 2 && argc != 3)
		otshib_ochka(cub_st, 8);
	else if (argc == 3 && (ft_strncmp("--save", argv[2], 7) == 0))
		cub_st->save = 1;
	else if (argc == 3)
		while (argv[2][i])
			if (!ft_isdigit(argv[2][i++]))
				otshib_ochka(cub_st, 8);
}

int			main(int argc, char **argv)
{
	int				fd;
	int				ret;
	t_cube			cub_st;
	int				i;

	ret = 1;
	init_struct(&cub_st);
	check_argc(argc, argv, &cub_st);
	chek_type_first_arg(argv[1], &cub_st);
	if ((!(fd = open((argv[1]), O_RDONLY)) || fd < 0))
		otshib_ochka(&cub_st, 1);
	while (ret)
	{
		if (!(ret = get_next_line(fd, &cub_st.line)))
			break ;
		first_part_params(cub_st.line, &cub_st, &i);
	}
	if (cub_st.line)
		free(cub_st.line);
	if (cub_st.lines != 8)
		otshib_ochka(&cub_st, 6);
	map_proc(&cub_st, argv[1]);
	go_to_screen(&cub_st);
	return (0);
}
