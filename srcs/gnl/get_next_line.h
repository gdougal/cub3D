/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdougal <gdougal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 07:09:12 by gdougal           #+#    #+#             */
/*   Updated: 2020/07/20 07:09:48 by gdougal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
char	*ft_g_strchr(const char *s, int c);
size_t	ft_g_strlen(const char *s);
char	*ft_g_strjoin(char const *s1, char const *s2);
char	*ft_g_strdup(const char *s);

#endif
