/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pers_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:28:19 by gdougal           #+#    #+#             */
/*   Updated: 2020/11/01 20:28:22 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	sprite_pos(t_all *vars, t_cnt *cnt, t_list **lst_copy)
{
	t_sprt	*sprt;

	sprt = malloc(sizeof(t_sprt));
	sprt->x = (float)(cnt->cnt_2 + 0.5);
	sprt->y = (float)(cnt->cnt_1 + 0.5);
	if (!vars->list_1)
	{
		*lst_copy = ft_lstnew(sprt);
		vars->list_1 = *lst_copy;
	}
	else
		ft_lstadd_back(&(*lst_copy), ft_lstnew(sprt));
}

static void	pers_pos_conds(t_all *vars, t_cube *pars, t_cnt *cnt)
{
	if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'N')
	{
		vars->loc.v_vis = 'N';
		vars->loc.x = (float)(cnt->cnt_2 + 0.5);
		vars->loc.y = (float)(cnt->cnt_1 + 0.5);
	}
	else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'W')
	{
		vars->loc.v_vis = 'W';
		vars->loc.x = (float)(cnt->cnt_2 + 0.5);
		vars->loc.y = (float)(cnt->cnt_1 + 0.5);
	}
	else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'S')
	{
		vars->loc.v_vis = 'S';
		vars->loc.x = (float)(cnt->cnt_2 + 0.5);
		vars->loc.y = (float)(cnt->cnt_1 + 0.5);
	}
	else if (pars->map[cnt->cnt_1][cnt->cnt_2] == 'E')
	{
		vars->loc.v_vis = 'E';
		vars->loc.x = (float)(cnt->cnt_2 + 0.5);
		vars->loc.y = (float)(cnt->cnt_1 + 0.5);
	}
}

void		pers_position(t_all *vars, t_cube *pars, t_cnt *cnt)
{
	t_list	*lst_copy;

	null_cnt(vars);
	while (pars->map[cnt->cnt_1])
	{
		while (pars->map[cnt->cnt_1][cnt->cnt_2])
		{
			if (vars->loc.x == 0 && vars->loc.y == 0)
				pers_pos_conds(vars, pars, cnt);
			if (pars->map[cnt->cnt_1][cnt->cnt_2] == '2')
				sprite_pos(vars, &vars->cnt, &lst_copy);
			cnt->cnt_2++;
		}
		cnt->cnt_2 = 0;
		cnt->cnt_1++;
	}
	null_cnt(vars);
}
