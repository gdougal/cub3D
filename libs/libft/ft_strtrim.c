/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hh2000 <hh2000@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 02:44:39 by hh2000            #+#    #+#             */
/*   Updated: 2020/05/24 01:52:47 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		stlen_correct(char const *s1, char const *set)
{
	int		start;
	int		i;

	start = 0;
	i = 0;
	while (set[i])
	{
		i = 0;
		while (s1[start] != set[i] && set[i])
			i++;
		if (!set[i])
			break ;
		start++;
	}
	return (start);
}

static	int		endl_correct(char const *s1, char const *set, int stlen)
{
	int		i;
	int		endl;

	i = 0;
	endl = ft_strlen(s1 + stlen);
	while (set[i])
	{
		i = 0;
		while (s1[stlen + endl - 1] != set[i] && set[i])
			i++;
		if (!set[i])
			break ;
		endl--;
	}
	return (endl);
}

static	char	*trimm(char const *s1, int endl, int stlen)
{
	int		temp;
	char	*trimmed;

	trimmed = malloc((endl + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	temp = stlen;
	while (stlen < (temp + endl))
		*trimmed++ = s1[stlen++];
	*trimmed = '\0';
	return (trimmed - endl);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	int		stlen;
	int		endl;

	if (s1 == set || !s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	stlen = stlen_correct(s1, set);
	if (!s1[stlen])
		return (ft_strdup(""));
	endl = endl_correct(s1, set, stlen);
	trimmed = trimm(s1, endl, stlen);
	return (trimmed);
}
