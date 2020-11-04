/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:30:17 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:53:55 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *t;

	t = NULL;
	if (!*s && c)
		return (0);
	while (*s)
	{
		if (*s == c)
			t = s;
		s++;
	}
	return (char *)(c == '\0' ? s : t);
}
