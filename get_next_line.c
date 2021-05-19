/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/20 00:56:10 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_result(char *storage, int result, ssize_t read_cnt)
{
	int ret;

	if (read_cnt == -1)
		ret = (FLAG_ERROR);
	else if (read_cnt == 0 && storage == NULL)
		ret = FLAG_EOF;
	else
		ret = (result);
	return (ret);
}

int make_line(char **storage, char **line, ssize_t read_cnt)
{
	int		newline_idx;
	char	*temp;

	// printf("storage1\t[%s]\n", *storage);
	newline_idx = ft_strchr(*storage, '\n');
	// printf("idx\t\t%d\n", newline_idx);
	// printf("read_cnt\t%zd\n", read_cnt);
	// printf("storage2\t[%s]\n", *storage);
	if (newline_idx != -1 && newline_idx == read_cnt - 1) // 버퍼 끝이 개행임
	{
		storage[0][newline_idx] = '\0';
		*line = ft_strdup(storage[0]);
		*storage = NULL;
	}
	else
	{
		if (newline_idx == -1) // 개행이 없음 (EOF)
		{
			*line = ft_strdup(*storage);
			*storage = NULL;
		}
		else
		{
			storage[0][newline_idx] = '\0';
			*line = ft_strdup(*storage);
			// free(*storage);
			temp = ft_strdup(storage[0] + newline_idx + 1);
			*storage = temp;
		}
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
	// printf("buf [%s] \n", buf);
	newline_idx = ft_strchr(buf, '\n');
	if (*storage != NULL)
	{
		temp = ft_strdup(*storage);
		// free(*storage);
	}
	*storage = temp == NULL ? ft_strdup(buf) : ft_strjoin(temp, buf);
	return (newline_idx);
}

int	read_line(ssize_t *read_cnt, char **storage, int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			newline_idx;

	// if (*storage != NULL)
	// {
	// 	return (make_line(storage, line, *read_cnt));
	// }
	// else
	// {

		while ((*read_cnt = read(fd, buf, BUFFER_SIZE)) && *read_cnt != -1)
		{
			buf[*read_cnt] = '\0';
			// printf("read_cnt [%zd] \n", *read_cnt);
			// printf("buf [%s] \n", buf);
			newline_idx = save_line(storage, buf);
			// printf("newline_idx %d \n", newline_idx);
			// printf("storage %s \n", *storage);
			if (newline_idx != -1)
				return (FLAG_SUCCESS);
		}

		if (*read_cnt == -1)
			return (FLAG_ERROR);
		return (FLAG_EOF); // read_cnt가 0일 경우
	// }
}

int	get_next_line(int fd, char **line)
{
	static char *storage;
	ssize_t		read_cnt;
	int			result;

	if (*line)
		*line = (char *)malloc(sizeof(char) * 1);
	if (BUFFER_SIZE < 1 || fd < 0)
		return (FLAG_ERROR);
	result = read_line(&read_cnt, &storage, fd);
	if (result == -1)
		return (-1);
	if (storage != NULL)
		result = make_line(&storage, line, read_cnt);
	return (get_result(storage, result, read_cnt));
}
