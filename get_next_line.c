/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 16:58:28 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/21 17:11:38 by yejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char		*end;
	int			rd_size;
	static char	*tmp;

	if (!line)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char) * (BUFFSIZE + 1))))
		return (-1);
	if((end = ft_strchr(tmp, '\n')))
		{
			*end = 0;
			*line = tmp;
			tmp = ft_strdup(end + 1);
			return (1);
		}
	if ((rd_size = read(fd, *line, BUFFSIZE)) == -1)
		return (-1);
	while(rd_size > 0)
	{
		(*line)[rd_size] = 0;
		if((end = ft_strchr(*line, '\n')))
		{
			*end = 0;
			if (tmp)
			{
				if (!(*line = ft_strjoin(tmp, *line)))
					return (-1);
			}
			tmp = ft_strdup(end + 1);
			return (1);
		}
		else
		{
			if (!tmp)
			{
				if (!(tmp = ft_strdup(*line)))
					return (-1);
			}
			else
				if (!(tmp = ft_strjoin(tmp, *line)))
				{
					free(tmp);
					tmp = 0;
					return (-1);
				}
		}
		if ((rd_size = read(fd, *line, BUFFSIZE)) == -1)
		return (-1);
	}
	*line = tmp;
	return (0);

}
