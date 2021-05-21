/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:12:49 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/21 18:25:06 by yejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_tmp(char **tmp, char **line)
{
	char	*end;

	if((end = ft_strchr(*tmp, '\n')))
	{
		*end = 0;
		free(line);
		*line = *tmp;
		*tmp = ft_strdup(end + 1);
		return (1);
	}
	return (0);
}

int	check_line(char **tmp, char **line)
{
	char	*end;

	if((end = ft_strchr(*line, '\n')))
	{
		*end = 0;
		if(*tmp)
			if(!(*line = ft_strjoin(*tmp, *line)))
				return (-1);
		*tmp = ft_strdup(end + 1);
		return (1);
	}
	else
		if (!*tmp)
		{
			if (!(*tmp = ft_strdup(*line)))
				return (-1);
		}
		else
			if (!(*tmp = ft_strjoin(*tmp, *line)))
			{
				free(*tmp);
				*tmp = 0;
				return (-1);
			}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int			rd_size;
	static char	*tmp;
	int			rt;

	if(!line)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * (BUFFSIZE + 1))))
		return (-1);
	if (check_tmp(&tmp, line))
		return (1);
	if ((rd_size = read(fd, *line, BUFFSIZE)) == -1)
		return (-1);
	while(rd_size > 0)
	{
		(*line)[rd_size] = 0;
		if ((rt = check_line(&tmp, line)))
			return (rt);
		if ((rd_size = read(fd, *line, BUFFSIZE)) == -1)
			return (-1);
	}
	*line = tmp;
	return (0);
}
