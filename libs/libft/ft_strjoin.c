/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hh2000 <hh2000@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 01:57:59 by hh2000            #+#    #+#             */
/*   Updated: 2020/05/24 01:54:34 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*sum;

	if (!s1 || !s2)
		return (!s1 ? (char*)s2 : (char*)s1);
	i = ft_strlen(s1);
	i += ft_strlen(s2);
	sum = malloc((i + 1) * sizeof(char));
	if (!sum)
		return (0);
	while (*s1)
		*sum++ = *s1++;
	while (*s2)
		*sum++ = *s2++;
	*sum = '\0';
	return (sum - i);
}
