/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:30:48 by gdougal           #+#    #+#             */
/*   Updated: 2020/07/20 07:10:38 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_g_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != c)
	{
		if (*(s + i) == '\0')
			return (0);
		i++;
	}
	return (((char*)s + i));
}

size_t	ft_g_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_g_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*sum;

	if (!s1 || !s2)
		return (!s1 ? (char*)s2 : (char*)s1);
	i = ft_g_strlen(s1);
	i += ft_g_strlen(s2);
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

char	*ft_g_strdup(const char *s)
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
