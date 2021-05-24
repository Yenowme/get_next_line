/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:20:52 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/24 17:42:21 by yejeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char* line;
	int	check;
	int	fd;

	// fd = open("test.txt", O_RDONLY);
	fd = 1000;
	while ((check = get_next_line(fd, &line)) > 0)
	{
		printf("read = %s\n rt = %d", line, check);
		free(line);
	}
	if (check == -1)
	{
		printf("error read = %s \n", line);
		return (-1);
	}
	printf("last = %s\n rt = %dn", line, check);
	free(line);

	return (1);
}
