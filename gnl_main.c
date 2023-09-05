/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: north <north@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:32:34 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/05 21:56:08 by north            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd[25];
	char	*file[25];
	size_t	i;
	size_t	j;

	file[0] = "tests/test0.txt";
	file[1] = "tests/test1.txt";
	file[2] = "tests/test2.txt";
	file[3] = "tests/test3.txt";
	file[4] = "tests/test4.txt";
	file[5] = "tests/test5.txt";
	file[6] = "tests/test6.txt";
	file[7] = "tests/test7.txt";
	file[8] = "tests/test8.txt";
	file[9] = "tests/test9.txt";
	file[10] = "tests/test10.txt";
	file[11] = "tests/test11.txt";
	file[12] = "tests/test12.txt";
	file[13] = "tests/test13.txt";
	file[14] = "tests/test14.txt";
	file[15] = "tests/test15.txt";
	file[16] = "tests/test16.txt";
	file[17] = "tests/test17.txt";
	file[18] = "tests/test18.txt";
	file[19] = "tests/test19.txt";
	file[20] = "tests/test20.txt";
	file[21] = "tests/test21.txt";
	file[22] = "tests/test22.txt";
	file[23] = "tests/test23.txt";
	file[24] = "tests/test24.txt";
	line = NULL;
	i = 0;
	while (i < 25)
	{
		fd[i] = open(file[i], O_RDONLY);
		if (fd[i] == -1)
		{
			printf("Error opening file: %s\n", file[i]);
			return (1);
		}
		j = 0;
		while (j < 100)
		{
			printf("\n---------------------------------\n");
			line = get_next_line(fd[i]);
			printf("file[%02zu] line[%02zu]: %s", i, j, line);
			if (!line)
			{
				printf("\n---------------------------------\n");
				printf("End of file[%02zu]\n", i);
				break ;
			}
			if (line)
				free(line);
			line = NULL;
			j++;
		}
		close(fd[i]);
		i++;
	}
	system("leaks a.out");
	return (0);
}
