/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hh2000 <hh2000@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:41:21 by hh2000            #+#    #+#             */
/*   Updated: 2020/05/24 01:55:06 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	lines(char const *s, char c)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			j++;
	return (j);
}

static	int	tabs(char **ar, char *t, char c)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (*t)
	{
		i = 0;
		while (*(t + i) != c && *(t + i))
			++i;
		if (i > 0)
		{
			if(!(ar[j] = ft_substr(t, 0, i)))
				while(k < j)
					free(ar[k++]);
			if (k != 0)
				return (1);
			j++;
			t = t + i - 1;
		}
		t++;
	}
	return (0);
}

char		**ft_split(char const *s, char c)
{
	char	**ar;
	char	*t;
	int		j;

	if (!s)
		return (NULL);
	j = lines(s, c);
	t = (char *)s;
	if(!(ar = (char**)malloc((j + 1) * sizeof(char*))))
		return (NULL);
	ar[j] = NULL;
	if(tabs(ar, t, c))
	{
		free(ar);
		return (NULL);
	}
	else
		return (ar);
}
