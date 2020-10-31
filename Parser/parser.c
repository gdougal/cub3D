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


void		map_validation(t_cube_struct *cub_st, int i, int j)
{
	int	x;
	int y;

	y = i;
	x = j;
	if (i == 0 || j == 0 || j == (int)cub_st->height || i == (int)cub_st->width)
		cub_st->errno = 0;
	while (cub_st->map[x][y] != '1' && cub_st->errno == -1 && y < (int)cub_st->width)
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			cub_st->errno = 0;
		y++;
	}
	y = i;
	while (cub_st->map[x][y] != '1' && cub_st->errno == -1 && y >= 0)
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			cub_st->errno = 0;
		y--;
	}
	y = i;
	while (cub_st->map[x][y] != '1' && cub_st->errno == -1 && x < (int)cub_st->height)
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			cub_st->errno = 0;
		x++;
	}
	x = j;
	while (cub_st->map[x][y] != '1' && cub_st->errno == -1 && x >= 0)
	{
		if (cub_st->map[x][y] == ' ' || cub_st->map[x][y] == '\0')
			cub_st->errno = 0;
		x--;
	}
}


void	valid_sym_map(char *tmp, t_cube_struct *cub_st)
{
	int	i;

	i = 0;
	while (cub_st->errno ==  -1 && tmp[i])
	{
		if (!ft_strchr("012NEWS ", tmp[i]))
			cub_st->errno = 0;
		if (ft_strchr("NEWS", tmp[i]))
			cub_st->player++;
		i++;
	}
	if (i == 0)
		cub_st->errno = 0;
}

void 		del(void *content)
{
	free(content);
}



void 		map_reproc(t_cube_struct *cub_st)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	if(cub_st->errno == -1)
	{
		tmp = cub_st->list_f;
		cub_st->map = (char **) malloc(sizeof(char *) * (int)(cub_st->height));
		while (i < (int) cub_st->height)
		{
			cub_st->map[i] = ft_calloc((cub_st->width + 1), sizeof(char));
			i++;
		}
		cub_st->map[i] = NULL;
		i = 0;
		while (tmp && cub_st->errno == -1)
		{
			valid_sym_map((char *) tmp->content, cub_st);
			ft_strlcpy(cub_st->map[i], tmp->content, (ft_strlen(tmp->content) + 1));
			tmp = tmp->next;
			i++;
		}
		if (cub_st->player != 1)
			cub_st->errno = 0;
		ft_lstclear(&cub_st->list_f, del);
		j = 0;
		while (j < cub_st->height - 1 && cub_st->errno == -1)
		{
			i = 0;
			while (cub_st->map[j][i] && cub_st->errno == -1)
			{
				if (cub_st->map[j][i] == '0' || cub_st->map[j][i] == 'N' || cub_st->map[j][i] == 'S' ||
					cub_st->map[j][i] == 'W' || cub_st->map[j][i] == 'E' || cub_st->map[j][i] == '2')
					map_validation(cub_st, i, j);
				i++;
			}
			j++;
		}
	}
}


static void	map_proc(float height, t_cube_struct *cub_st, char *argv)
{
	int		fd;
	int		ret = 1;
	char	*line;
	t_list	*tmp;
	int		flag = 0;

	if (cub_st->errno == -1)
	{
		fd = open(argv, O_RDONLY);
		cub_st->map = (char **) malloc((int) (height + 1) * sizeof(char *));
		while (ret > 0 && cub_st->errno == -1)
		{
			ret = get_next_line(fd, &line);
			if (flag && line[0] == '\0')
				cub_st->errno = 0;
			if ((line[0] == '1' || line[0] == ' ') && cub_st->errno == -1)
			{
				flag = 1;
				cub_st->width = (ft_strlen(line) > cub_st->width ? ft_strlen(line) : cub_st->width);
				if (!cub_st->list_f && cub_st->errno == -1)
				{
					tmp = ft_lstnew(line);
					cub_st->list_f = tmp;
				} else if (cub_st->errno == -1)
					ft_lstadd_back(&tmp, ft_lstnew(line));
				cub_st->height++;
			}
			else
				free(line);
		}
//		free(line);
		if (!flag)
			cub_st->errno = 0;
	}
}

static void	proc_path(char *line, char l, t_cube_struct *cub_st)
{
	if (l == 'N')
		cub_st->path[0] = ft_strtrim(line, "NO ");
	else if (l == 'S')
		cub_st->path[2] = ft_strtrim(line, "SO ");
	else if (l == 'W')
		cub_st->path[3] = ft_strtrim(line, "WE ");
	else if (l == 'E')
		cub_st->path[1] = ft_strtrim(line, "EA ");
	else if (l == 's')
		cub_st->path[4] = ft_strtrim(line, "S ");
	cub_st->lines++;
}

int	create_trgb(int t, int r, int g, int b)
{
    return(t << 24 | r << 16 | g << 8 | b);
}


static void	resol_pars(t_cube_struct *cub_st, char **tmp, int j)
{
	int i;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		cub_st->errno = 2;
	i = 0;
	while (tmp[j][i])
		if (!(ft_isdigit(tmp[j][i++])))
			cub_st->errno = 2;

	if (j == 1 && i < 6)
		cub_st->res_x = ft_atoi(tmp[j]);
	else if (j == 1 && i >= 6)
		cub_st->res_x = 2560;
	if (j == 2 && i < 6)
		cub_st->res_y = ft_atoi(tmp[2]);
	else if (j == 2 && i >= 6)
		cub_st->res_y = 1440;
	if (cub_st->res_x == 0 || cub_st->res_y == 0)
		cub_st->errno = 2;

}

static void	colour_pars(t_cube_struct *cub_st, char **tmp, int k)
{
	int	i;
	int j;

	j = 0;
	while(tmp[j])
		j++;
	if(j == 3)
	{
		j = 0;
		while (tmp[j])
		{
			i = 0;
			while (tmp[j][i])
				if (!(ft_isdigit(tmp[j][i++])))
					cub_st->errno = 3;
			j++;
		}
		if (k == 1 && ft_atoi(tmp[0]) <= 255 && ft_atoi(tmp[1]) <= 255 && ft_atoi(tmp[2]) <= 255)
			cub_st->flor_clr = (unsigned int)create_trgb(0, ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		else if (k == 2 && ft_atoi(tmp[0]) <= 255 && ft_atoi(tmp[1]) <= 255 && ft_atoi(tmp[2]) <= 255)
			cub_st->ceilling_clr = (unsigned int)create_trgb(0, ft_atoi(tmp[0]), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
		else
			cub_st->errno = 3;
	}
	else
		cub_st->errno = 3;
}

static void	proc_numbers(char *line, char l, t_cube_struct *cub_st)
{
	char	**tmp;
	int 	i;

	tmp = NULL;
	if ((l == 'R' || l == 'F' || l == 'C') && cub_st->errno == -1)
	{
		if (l == 'R' && cub_st->errno == -1)
		{
			tmp = ft_split(line, ' ');
			resol_pars(cub_st, tmp, 1);
			resol_pars(cub_st, tmp, 2);
			cub_st->lines++;
		}
		else if (l == 'F' && cub_st->errno == -1)
		{
			tmp = ft_split(ft_strtrim(line, "F "), ',');
			colour_pars(cub_st, tmp, 1);
			cub_st->lines++;
		}
		else if (l == 'C' && cub_st->errno == -1)
		{
			tmp = ft_split(ft_strtrim(line, "C "), ',');
			colour_pars(cub_st, tmp, 2);
			cub_st->lines++;
		}
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
}

static void	init_struct(t_cube_struct *cub_st)
{
	int i = 0;
	cub_st->errno = -1;
	cub_st->lines = 0;
	cub_st->res_x = -1;
	cub_st->res_y = -1;
	cub_st->flor_clr = 0;
	cub_st->ceilling_clr = 0;
	while (i <= 5)
		cub_st->path[i++] = NULL;
	cub_st->map = NULL;
	cub_st->width = 0;
	cub_st->height = 0;
	cub_st->list_f = NULL;
	cub_st->player = 0;
}

void 					otshib_ochka(t_cube_struct *cub_st)
{
	int	i;
	i = 0;
	char **er;

	if (cub_st->errno != -1)
	{

		char tmp[221] = "invalid map format.\n+invalid map-file.\n"
						"+wrong resolution params.\n+invalid floor/ceilling colour.\n+"
						"invalid path to texture.\n+invalid texture format.\n+"
						"invalid number of textures.\n+expected colour/ceilling or floor.\n";
		er = ft_split(tmp, '+');
		ft_putstr_fd(ft_strjoin("Error\n", er[cub_st->errno]), 1);
		while(er[i])
			free(er[i++]);
	}
	i = 0;
	while (cub_st->path[i])
	{
		free(cub_st->path[i]);
		cub_st->path[i] = NULL;
		i++;
	}
	exit(0);
}


void		chek_type_first_arg(char *arg, t_cube_struct *cub_st)
{
	int i;

	i = 0;
	if (arg)
	{
		while (arg[i])
			i++;
		if (ft_memcmp((arg + (i - 4)), ".cub", 4))
			cub_st->errno = 0;
	}
	else
		cub_st->errno = 0;
}


int			main(int argc, char **argv)
{
	int fd;
	char *line;
	int ret = 1;
	t_cube_struct cub_st;

	init_struct(&cub_st);
	chek_type_first_arg(argv[1], &cub_st);
	if ((!(fd = open((argv[1]), O_RDONLY)) || fd < 0) && cub_st.errno == -1)
		cub_st.errno = 1;
	while (ret && cub_st.errno == -1)
	{
		if (!(ret = get_next_line(fd, &line)))
			break;
		if (line[0] == 'R' && cub_st.errno == -1 && cub_st.res_y == -1 && cub_st.res_x == -1)
			proc_numbers(line, 'R', &cub_st);
		else if (line[0] == 'R' && cub_st.res_y != -1 && cub_st.res_x != -1)
			cub_st.errno = 0;
		else if (line[0] == 'F' && cub_st.errno == -1)
			proc_numbers(line, 'F', &cub_st);
		else if (line[0] == 'C' && cub_st.errno == -1)
			proc_numbers(line, 'C', &cub_st);
		else if (!ft_memcmp(line, "NO", 2) && cub_st.errno == -1)
			proc_path(line, 'N', &cub_st);
		else if (!ft_memcmp(line, "SO", 2) && cub_st.errno == -1)
			proc_path(line, 'S', &cub_st);
		else if (!ft_memcmp(line, "WE", 2) && cub_st.errno == -1)
			proc_path(line, 'W', &cub_st);
		else if (!ft_memcmp(line, "EA", 2) && cub_st.errno == -1)
			proc_path(line, 'E', &cub_st);
		else if (line[0] == 'S' && cub_st.errno == -1)
			proc_path(line, 's', &cub_st);
		free(line);
	}
	if (cub_st.lines != 8 && cub_st.errno == -1)
		cub_st.errno = 7;
	if (cub_st.errno == -1)
		map_proc(cub_st.height, &cub_st, argv[1]);
	if (cub_st.errno == -1)
		map_reproc(&cub_st);
	if (cub_st.errno != -1)
		otshib_ochka(&cub_st);
	go_to_screen(&cub_st);
    return((cub_st.errno > -1 ? 1 : 0));
}