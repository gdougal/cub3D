/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:05:10 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/08 15:05:15 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Make map validation (compare with nearest elements, + \0)
// Make other params validation
// Normalization cod-style
// Functions length

static void				max_line(t_cube_struct *cube_struct)
{
	int	nil;
	int j;

	j = 0;
	while(cube_struct->map[j])
	{
		nil = (int)ft_strlen(cube_struct->map[j++]);
		cube_struct->width = (cube_struct->width > nil ? cube_struct->width : nil);
	}
}

static void	map_proc(int height, t_cube_struct *cube_struct, char *argv)
{
	int		count;
	int		fd;
	int		ret;
	char	*line;

	fd = open(argv, O_RDONLY);
	count = 0;
	cube_struct->map = (char**)malloc((height + 1) * sizeof(char*));
	do
	{
		line = (char *)malloc(sizeof(*line) * 1);
		ret = get_next_line(fd, &line);
		if (line[0] == '1' || line[0] == '0' || line[0] == '2' || line[0] == ' ')
		{
			cube_struct->map[count] = ft_strdup(line);
			count++;
		}
	}
	while (ret);
	cube_struct->map[count] = NULL;
	free(line);
}

static void	proc_path(char *line, char l, t_cube_struct *cube_struct)
{
	if (l == 'N')
		cube_struct->path_n = ft_strtrim(line, "NO ");
	else if (l == 'S')
		cube_struct->path_s = ft_strtrim(line, "SO ");
	else if (l == 'W')
		cube_struct->path_w = ft_strtrim(line, "WE ");
	else if (l == 'E')
		cube_struct->path_e = ft_strtrim(line, "EA ");
	else if (l == 's')
		cube_struct->path_sprite = ft_strtrim(line, "S ");
}

int	create_trgb(int t, int r, int g, int b)
{
    return(t << 24 | r << 16 | g << 8 | b);
}

static void	proc_numbers(char *line, char l, t_cube_struct *cube_struct)
{
	char **tmp;

	tmp = NULL;
	if (l == 'R' || l == 'F' || l == 'C')
	{
		if (l == 'R')
		{
			tmp = ft_split(line, ' ');
			cube_struct->res_x = ft_atoi(tmp[1]);
			cube_struct->res_y = ft_atoi(tmp[2]);
		}
		if (l == 'F')
		{
			tmp = ft_split(ft_strtrim(line, "F "), ',');
			cube_struct->flor_clr = (unsigned int)create_trgb(0, ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		}
		if (l == 'C')
		{
			tmp = ft_split(ft_strtrim(line, "C "), ',');
			cube_struct->ceilling_clr = (unsigned int)create_trgb(0, ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		}
	}
	free(tmp);
}

static void	init_struct(t_cube_struct *cube_struct)
{

	cube_struct->res_x = -1;
	cube_struct->res_y = -1;
	cube_struct->flor_clr = 1;
	cube_struct->ceilling_clr = 1;
	cube_struct->path_n = "0000";
	cube_struct->path_s = "0000";
	cube_struct->path_w = "0000";
	cube_struct->path_e = "0000";
	cube_struct->path_sprite = "0000";
	cube_struct->map = NULL;
	cube_struct->width = 0;
	cube_struct->height = 0;
}

int						main(int argc, char **argv)
{
    int				fd;
    char			*line;
    int				ret;
	t_cube_struct	cube_struct;

    (void)argc;
    fd = open((argv[1]), O_RDONLY);
    init_struct(&cube_struct);
    do
    {
        line = (char *)malloc(sizeof(*line) * 1);
        ret = get_next_line(fd, &line);
        if (line[0] == 'R')
			proc_numbers(line, 'R', &cube_struct);
        else if (line[0] == 'F')
			proc_numbers(line, 'F', &cube_struct);
        else if (line[0] == 'C')
			proc_numbers(line, 'C', &cube_struct);
        else if (!ft_memcmp(line, "NO", 2))
			proc_path(line, 'N', &cube_struct);
        else if (!ft_memcmp(line, "SO", 2))
			proc_path(line, 'S', &cube_struct);
        else if (!ft_memcmp(line, "WE", 2))
			proc_path(line, 'W', &cube_struct);
        else if (!ft_memcmp(line, "EA", 2))
			proc_path(line, 'E', &cube_struct);
        else if (line[0] == 'S')
			proc_path(line, 's', &cube_struct);
        else if (line[0] == '1' || line[0] == '0' || line[0] == 'N' || line[0] == '2' || line[0] == ' ')
			cube_struct.height++;
    }
    while (ret);
	map_proc(cube_struct.height, &cube_struct, argv[1]);
	free(line);
	max_line(&cube_struct);
	go_to_screen(&cube_struct);
	free(&cube_struct);
    return(0);
}