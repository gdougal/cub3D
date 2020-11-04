/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:33:26 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:57:46 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char *t;

	t = malloc(nmemb * size);
	if (!t)
		return (NULL);
	nmemb *= size;
	while (nmemb--)
		t[nmemb] = '\0';
	return (t);
}
