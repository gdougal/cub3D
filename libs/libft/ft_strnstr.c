/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 17:44:03 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 12:30:07 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t j;

	if (!*little || big == little)
		return ((char*)big);
	while (*big && len)
	{
		j = 0;
		while (*(big + j) == *(little + j) && len > j)
			if (*(little + ++j) == '\0')
				return ((char*)big);
		big++;
		len--;
	}
	return (0);
}
