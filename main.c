/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejeong <yejeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 15:20:52 by yejeong           #+#    #+#             */
/*   Updated: 2021/05/21 14:37:24 by yejeong          ###   ########.fr       */
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

	fd = open("test.txt", O_RDONLY);
	while ((check = get_next_line(fd, &line)) > 0)
	{
		printf("read = %s\n", line);
		free(line);
	}
	if (check == -1)
	{
		printf("error");
		return (-1);
	}
	printf("last = %s\n", line);
	free(line);

	return (1);
}
