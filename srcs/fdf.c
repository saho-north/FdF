/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/09/07 05:45:44 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_map
{
	int		width;
	int		height;
	int		**grid;
}			t_map;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

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

static bool	is_valid_after_minus(const char *str)
{
	while (*str == '0')
		str++;
	if (!ft_isdigit(*str))
		return (false);
	return (true);
}

static void	check_line(const char *line)
{
	const char	*str;

	str = line;
	while (*str)
	{
		if (*str == '-' && !is_valid_after_minus(++str))
		{
			write(2, "Error: Invalid character\n", 26);
			free((void *)line);
			exit(EXIT_FAILURE);
		}
		if (!ft_isdigit(*str))
		{
			write(2, "Error: Invalid character\n", 26);
			free((void *)line);
			exit(EXIT_FAILURE);
		}
		while (ft_isdigit(*str))
			str++;
		if (*str == ',' && !ft_isxdigit(*(++str)))
		{
			write(2, "Error: Invalid character\n", 26);
			free((void *)line);
			exit(EXIT_FAILURE);
		}
		if (!ft_isdigit(*line) && *line != ' ')
		{
			write(2, "Error: Invalid character\n", 26);
			exit(EXIT_FAILURE);
		}
		line++;
	}
}

static void	open_file(const char *filename)
{
	int			fd;
	const char	*line;
	size_t		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (true)
	{
		line = (const char *)get_next_line(fd);
		if (!line)
			break ;
		check_line(line);
		printf("%s", line);
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
}

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
	open_file(argv[1]);
	printf("Hello, world!\n");
	return (0);
}
