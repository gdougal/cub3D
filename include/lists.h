/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 19:35:07 by gdougal           #+#    #+#             */
/*   Updated: 2020/10/24 19:35:09 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LISTS_H
# define LISTS_H

#include "struct.h"

t_sprt	*sprt_coord_lstlast(t_sprt *lst);
void	sprt_coord_lstadd_back(t_sprt **lst, t_sprt *new);
t_sprt	*sprt_coord_lstnew(t_sprt *sprt);

#endif //UNTITLED_LISTS_H
