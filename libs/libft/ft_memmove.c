/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 13:39:38 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:56:36 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	temp;
	size_t	i;

	i = 0;
	if (dest > src && dest + n >= src)
	{
		i = n;
		while (n > 0 && dest != src)
		{
			temp = *(char *)(src + n - 1);
			*(char *)(dest + n - 1) = temp;
			n--;
		}
	}
	else
	{
		while (i < n && dest != src)
		{
			temp = *(char *)(src + i);
			*(char *)(dest + i) = temp;
			i++;
		}
	}
	return (dest);
}
