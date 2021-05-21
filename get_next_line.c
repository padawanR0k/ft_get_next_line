/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/20 23:49:31 by yurlee           ###   ########.fr       */
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

int	free_all(char **storage, int ret)
{
	free(*storage);
	return (ret);
}

int	make_line(char **storage, char **line)
{
	int		newline_idx;
	char	*temp;

	newline_idx = ft_strchr(*storage, '\n');
	if (newline_idx == -1)
	{
		if (!(*line = ft_strdup(storage[0])))
			return (free_all(storage, FLAG_ERROR));
		free(*storage);
		*storage = NULL;
	}
	else
	{
		storage[0][newline_idx] = '\0';
		if(!(*line = ft_strdup(storage[0])))
			return (free_all(storage, FLAG_ERROR));
		if(!(temp = ft_strdup(storage[0] + newline_idx + 1)))
			return (free_all(storage, FLAG_ERROR));
		free(*storage);
		*storage = temp;
	}
	return (*line == 0 ? FLAG_ERROR : 1);
}

int	read_line(ssize_t *read_cnt, char **storage, int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			newline_idx;
	char		*temp;

	while ((*read_cnt = read(fd, buf, BUFFER_SIZE)) && *read_cnt != -1)
	{
		buf[*read_cnt] = '\0';
		temp = NULL;
		newline_idx = ft_strchr(buf, '\n');
		if (*storage != NULL)
		{
			if (!(temp = ft_strdup(*storage)))
				return (free_all(storage, FLAG_ERROR));
			else
				free(*storage);
		}
		if (!(*storage = temp == NULL ? ft_strdup(buf) : ft_strjoin(temp, buf)))
			return (free_all(storage, FLAG_ERROR));
		else
			free(temp);
		if (newline_idx != -1)
			return (FLAG_SUCCESS);
	}
	return (*read_cnt == -1 ? FLAG_ERROR : 0);
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
	// if (*line)
	// 	*line = (char *)malloc(sizeof(char) * 1);
	// else
	// {
	if (read_cnt == 0 && storage == NULL)
	{
		*line = (char *)malloc(sizeof(char) * 1);
		*line[0] = '\0';
	}
	// }
	if (storage != NULL)
		result = make_line(&storage, line);
	return (get_result(storage, result, read_cnt));
}
