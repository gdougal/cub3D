/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hh2000 <hh2000@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:57:09 by hh2000            #+#    #+#             */
/*   Updated: 2020/05/24 11:56:56 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i <= start)
		return (ft_strdup(""));
	i = len > (i - start) ? (i - start) : len;
	if(!(sub = malloc((i + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(sub, s + start, i + 1);
	return (sub);
}
