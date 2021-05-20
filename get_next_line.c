/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/20 18:45:23 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_result(char *storage, int result, ssize_t read_cnt)
{
	int ret;

	if (read_cnt == -1)
		ret = (FLAG_ERROR);
	else if (read_cnt < BUFFER_SIZE && storage == NULL)
		ret = FLAG_EOF;
	else
		ret = (result);
	return (ret);
}

int make_line(char **storage, char **line)
{
	int		newline_idx;
	char	*temp;

	newline_idx = ft_strchr(*storage, '\n');
	if (newline_idx == -1)
	{
		*line = ft_strdup(*storage);
		*storage = NULL;
	}
	else
	{
		storage[0][newline_idx] = '\0';
		*line = ft_strdup(storage[0]);
		temp = ft_strdup(storage[0] + newline_idx + 1);
		*storage = temp;
	}
	return (*line == 0 ? FLAG_ERROR : 1);
}

/**
 * storage에 개행을 기준으로 좌측에 나타나는 값들을 저장한다.
 **/
int	save_line(char **storage, char *buf)
{
	int			newline_idx;
	char		*temp;

	temp = NULL;
	newline_idx = ft_strchr(buf, '\n');
	if (*storage != NULL)
		temp = ft_strdup(*storage);
	*storage = temp == NULL ? ft_strdup(buf) : ft_strjoin(temp, buf);
	return (newline_idx);
}

int	read_line(ssize_t *read_cnt, char **storage, int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			newline_idx;
	while ((*read_cnt = read(fd, buf, BUFFER_SIZE)) && *read_cnt != -1)
	{
		buf[*read_cnt] = '\0';
		newline_idx = save_line(storage, buf);
		if (newline_idx != -1)
			return (FLAG_SUCCESS);
	}
	if (*read_cnt == -1)
		return (FLAG_ERROR);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *storage;
	ssize_t		read_cnt;
	int			result;

	if (BUFFER_SIZE < 1 || fd < 0 || line == NULL)
		return (FLAG_ERROR);
	result = read_line(&read_cnt, &storage, fd);
	if (result == -1)
		return (-1);
	if (*line)
	{
		*line = (char *)malloc(sizeof(char) * 1);
		// *line[0] = '\0';
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * 1);
		*line[0] = '\0';
	}
	if (storage != NULL)
		result = make_line(&storage, line);
	return (get_result(storage, result, read_cnt));
}
