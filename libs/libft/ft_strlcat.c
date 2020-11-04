/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:22:39 by gdougal           #+#    #+#             */
/*   Updated: 2020/05/24 01:54:29 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	src_len = 0;
	while (dst[dst_len] && dst_len != size)
		dst_len++;
	src_len = ft_strlen(src);
	if (dst_len == size)
		return (size + src_len);
	else if (src_len < size - dst_len)
		ft_memcpy((dst + dst_len), src, (src_len + 1));
	else
	{
		ft_memcpy((dst + dst_len), src, (size - dst_len - 1));
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
