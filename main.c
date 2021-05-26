/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:20:52 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/26 16:05:34 by yejeong          ###   ########.fr       */
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

	fd = open("multiple_line_no_nl", O_RDONLY);
	// fd = 1000;
	while ((check = get_next_line(fd, &line)) > 0)
	{
		printf("read = %s rt = %d\n", line, check);
		free(line);
	}
	if (check == -1)
	{
		printf("error read = %s \n", line);
		return (-1);
	}
	printf("last = %s rt = %d\n", line, check);
	free(line);

	return (1);
}
