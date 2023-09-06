/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/07 02:29:36 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// typedef struct s_map
// {
// 	int		width;
// 	int		height;
// 	int		**grid;
// }			t_map;

 static bool	check_file_extension(const char *filename)
 {
 	size_t		len;
 	const char	*extension;

 	len = ft_strlen(filename);
 	if (len < 5)
 		return (false);
 	extension = &filename[len - 4];
 	return (ft_strncmp(extension, ".fdf", 4) == 0);
 }

// static void	open_file(const char *filename)
// {
// 	int		fd;
// 	char	**line;
// 	size_t	i;

// 	i = 0;
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while (true)
// 	{
// 		line[i] = get_next_line(fd);
// 		if (!line[i])
// 			break ;
// 		printf("%s\n", line[i]);
// 		i++;
// 	}
// 	close(fd);
// }

int	main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		write(2, "Usage: ./fdf <file_name>.fdf\n", 29);
		return (1);
	}
	if (!check_file_extension(argv[1]))
	{
		write(2, "Error: Invalid file extension\n", 30);
		return (1);
	}
	//open_file(argv[1]);
	printf("Hello, world!\n");
	system("leaks a.out");
	return (0);
}
