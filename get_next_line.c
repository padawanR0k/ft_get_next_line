/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/18 00:58:26 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 모두 합쳐보기
int get_next_line(int fd, char **line)
{
	static char *accumulator;
	int		read_cnt;
	int		result; // 0 1 -1
	char	buf[BUFFER_SIZE];
	char	*newline_idx;
	result = 0;
	while ((read_cnt = read(fd, buf, BUFFER_SIZE)) && read_cnt > 0)
	{
		result = read_cnt < BUFFER_SIZE ? 0 : 1;
		buf[BUFFER_SIZE - 1] = '\0';
		newline_idx = ft_strchr(buf, '\n');
		if (accumulator)
		{
			if (newline_idx == 0)
				accumulator = ft_strjoin(accumulator, buf);
			else
			{
				buf[newline_idx - buf - 1] = '\0';
				accumulator = ft_strjoin(accumulator, buf);
				*line = ft_strdup(accumulator);
				accumulator = ft_strjoin(accumulator, newline_idx + 2);
				return (1);
				// buf[newline_idx] ~ read_cnt 까지의 값은 어떻게 할 것인가?
			}
		}
		else
			accumulator = ft_strdup(buf);
		printf("buf: [%s] \n", buf);
		printf("accumulator: [%s] \n", accumulator);
	}

	return (result);
}