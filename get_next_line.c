/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:49 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/24 18:16:45 by yejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_tmp(char **tmp, char **line)
{
	char	*end;

	if ((end = ft_strchr(*tmp, '\n')))
	{
		*end = 0;
		free(*line);
		*line = *tmp;
		if (!(*tmp = ft_strdup(end + 1)))
			return (-1);
		return (1);
	}
	return (0);
}

int free_tmp(char *tmp, int rt)
{
	if (!ft_strlen(tmp))
	{
		free(tmp);
		tmp = 0;
	}
	return (rt);
}

static int	check_line(char **tmp, char **line)
{
	char	*end;

	if ((end = ft_strchr(*line, '\n')))
	{
		*end = 0;
		if (*tmp)
			if (!(*line = ft_strjoin(*tmp, *line)))
				return (-1);
		*tmp = ft_strdup(end + 1);
		return (free_tmp( *tmp, 1));
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

int	get_next_line(int fd, char **line)
{
	int			rd_size;
	static char	*tmp[OPEN_MAX];
	int			rt;

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || fd > OPEN_MAX)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!tmp[fd])
		if (!(tmp[fd] = ft_strdup("")))
			return (-1);
	if ((rt = check_tmp(&tmp[fd], line)))
		return (rt);
	if ((rd_size = read(fd, *line, BUFFER_SIZE)) == -1)
	{
		free(line);
		*line = 0;//?
		return (free_tmp(tmp[fd], -1));
	}
	while(rd_size > 0)
	{
		(*line)[rd_size] = 0;
		if ((rt = check_line(&tmp[fd], line)))
			return (rt);
		if ((rd_size = read(fd, *line, BUFFER_SIZE)) == -1)
			return (free_tmp(tmp[fd], -1));
	}
	free(*line);
	*line = tmp[fd];
	tmp[fd] = 0;
	return (0);
}
