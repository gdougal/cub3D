/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:18:18 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:54:41 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	t = malloc((i + 1) * sizeof(char));
	if (!t)
		return (NULL);
	t[i] = '\0';
	while (i--)
		t[i] = s[i];
	return (t);
}
