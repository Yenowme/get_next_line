/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:49 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/26 17:12:30 by yejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	check_tmp(char **tmp, char **line)
{
	char	*end;
	char	*buff;

	if (!*tmp)
		if (!(*tmp = ft_strdup("")))
			return (-1);
	if ((end = ft_strchr(*tmp, '\n')))
	{
		*end = 0;
		buff = *tmp;
		*line = ft_strdup(*tmp);
		if (!(*tmp = ft_strdup(end + 1)))
			return (-1);
		free(buff);
		return (1);
	}
	return (0);
}

static int	check_line(char **tmp, char **line)
{
	char	*end;
	char	*buff;

	if ((end = ft_strchr(*line, '\n')))
	{
		*end = 0;
		buff = *line;
		if (*tmp)
			if (!(*line = ft_strjoin(*tmp, *line)))
				return (-1);
		*tmp = ft_strdup(end + 1);
		free(buff);
		return (1);
	}
	else if (!*tmp)
	{
		if (!(*tmp = ft_strdup(*line)))
			return (-1);
	}
	else if (!(*tmp = ft_strjoin(*tmp, *line)))
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	int			rd_size;
	static char	*tmp[OPEN_MAX];
	int			rt;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > OPEN_MAX
	|| read(fd, *line, 0) == -1)
		return (-1);
	if ((rt = check_tmp(&tmp[fd], line)))
		return (rt);
	if (!(*line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((rd_size = read(fd, *line, BUFFER_SIZE)) == -1)
		return (-1);
	while (rd_size > 0)
	{
		(*line)[rd_size] = 0;
		if ((rt = check_line(&tmp[fd], line)))
			return (rt);
		if ((rd_size = read(fd, *line, BUFFER_SIZE)) == -1)
			return (-1);
	}
	free(*line);
	*line = tmp[fd];
	tmp[fd] = 0;
	return (0);
}
