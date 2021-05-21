/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:52:09 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/20 23:07:51 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# define FLAG_ERROR -1
# define FLAG_SUCCESS 1
# define FLAG_EOF 0

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int		ft_strchr(char *src, char c);
size_t	ft_strlen(const char *s);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
#endif