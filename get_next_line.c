/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yurlee <yurlee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 18:51:11 by yurlee            #+#    #+#             */
/*   Updated: 2021/05/19 00:43:46 by yurlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_newline_idx(char *str)
{
	int	idx;

	idx = 0;
	while(str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

int make_line(char **str_saved, char **line, char buf[BUFFER_SIZE + 1])
{
	int			newline_idx;
	char		*temp;

	newline_idx = get_newline_idx(buf);
	if (newline_idx != -1)
		buf[newline_idx] = '\0'; // 뉴라인 이후에 값들은 어디로???????
	temp = *str_saved ? ft_strdup(*str_saved) : ft_strdup("");
	free(*str_saved);
	*line = ft_strjoin(temp, buf); // 개행이 있으면 개행 전까지만 합친다.
	if (newline_idx == -1)
		*str_saved = ft_strjoin(temp, buf);
	else
		*str_saved = ft_strdup(buf + newline_idx + 1); // 개행이 등장한 뒤부터 저장한다.
	free(temp);
	return (newline_idx);
}

int get_next_line(int fd, char **line)
{
	static char *str_saved;
	ssize_t		read_cnt;
	int			result; // 0 1 -1
	char		buf[BUFFER_SIZE + 1];

	*line = (char *)malloc(1);
	result = -2;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (FLAG_ERROR);

	while ((read_cnt = read(fd, buf, BUFFER_SIZE)) && read_cnt != -1)
	{
		buf[read_cnt] = '\0';
		if (make_line(&str_saved, line, buf) != -1)
		{
			result = FLAG_SUCCESS; // 개행을 찾음.
			break ;
		}
	}
	if (read_cnt == -1)
		return (FLAG_ERROR);
	else if (result == 0)
		return (FLAG_SUCCESS);
	else if (result == -2)
	{
		if (str_saved)
		{
			free(str_saved);
			str_saved = NULL;
		}
		return (FLAG_EOF);
	}
	return (result);
}