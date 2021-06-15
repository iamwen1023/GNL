/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlo <wlo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:20:55 by wlo               #+#    #+#             */
/*   Updated: 2021/06/15 16:50:18 by wlo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;
	int		i;



	fd = open("try", O_RDONLY);

	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("\e[33mline READ:\e[0m\n|%s|\n", line);
		free(line);
	}
	if (i == -1)
		printf("\e[31mError encountered\e[0m\n");
	else if (!i)
		printf("\e[32mEOF reached\e[0m\n|%s|\n", line);
	else
		printf("Unexpected return of get_next_line\ni == %d\n", i);
	close(fd);
	//puts("\n");
	//system("leaks a.out");
	return (0);
}