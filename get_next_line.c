/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/14 19:32:13 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	static char *accumulator;
	int		read_cnt;
	int		result; // 0 1 -1
	char	buf[BUFFER_SIZE];

	while (read_cnt = read(fd, buf, BUFFER_SIZE))
	{
		if (accumulator)
			free(accumulator);
		accumulator = malloc(sizeof(char) * (strlen(*line) + strlen(buf) + 1));
		if (!accumulator)
			return (-1);
		accumulator = strlcat(*line, buf);
		free(*line);
		*line = accumulator;
	}

	return (result);
}