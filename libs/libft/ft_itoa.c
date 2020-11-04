/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hh2000 <hh2000@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:33:43 by hh2000            #+#    #+#             */
/*   Updated: 2020/05/24 01:57:34 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*num;
	int		num_order;
	int		i;
	int		sign;

	num_order = 1;
	i = n;
	sign = n < 0 ? -1 : 1;
	while (i /= 10)
		num_order++;
	i = (num_order + (sign - 3) / (-2));
	num = malloc(i * sizeof(char));
	if (!num)
		return (NULL);
	if (sign < 0)
		num[0] = '-';
	num[i - 1] = '\0';
	while (num_order)
	{
		num[(sign < 0 ? num_order-- : --num_order)] = (n % 10) * sign + '0';
		n /= 10;
	}
	return (num);
}
