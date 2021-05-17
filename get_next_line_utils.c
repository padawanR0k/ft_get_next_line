/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:42:02 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/18 00:35:22 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strdup(const char *s1)
{
	char *copy;
	long long len;
	long long idx;

	len = ft_strlen(s1);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	idx = 0;
	if (copy)
	{
		while (s1[idx])
		{
			copy[idx] = s1[idx];
			idx++;
		}
		copy[idx] = '\0';
		return (copy);
	}
	else
		return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*new_dst;
	unsigned char	*new_src;

	if (!dst && !src)
		return (0);
	i = 0;
	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		str_len;
	int		s1_len;
	int		s2_len;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	str_len = s1_len + s2_len;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (0);
	else
	{
		ft_memcpy(str, s1, s1_len);
		ft_memcpy(str + s1_len, s2, s2_len);
		str[s1_len + s2_len] = '\0';
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char		chr;

	chr = c;
	while (*(s))
	{
		if (*(s) == chr)
			return ((char *)(s));
		s++;
	}
	if (c == 0)
		return ((char *)(s));
	return (0);
}
