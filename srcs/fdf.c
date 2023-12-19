/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 00:17:49 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * fdf.c:
 * - main function
 * - memory allocation
 */

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

static void	check_read_status(t_read_status read_status)
{
	if (read_status == READ_ERROR)
	{
		perror("Error reading line");
		exit(EXIT_FAILURE);
	}
	if (read_status == READ_SUCCESS)
	{
		write(2, "Error: Unexpected null pointer\n", 31);
		exit(EXIT_FAILURE);
	}
	if (read_status == READ_EOF)
		write(1, "End of file reached.\n", 22);
}

static void	open_file(const char *filename)
{
	t_read_status	read_status;
	char			*line;
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	read_status = READ_SUCCESS;
	while (true)
	{
		line = get_next_line(fd, &read_status);
		if (!line)
		{
			check_read_status(read_status);
			break ;
		}
		check_line(line);
		printf("%s", line);
		free(line);
		line = NULL;
	}
	close(fd);
}

static size_t	check_last_char(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i == 0 || str[i - 1] == '\n')
	{
		return (0);
	}
	return (1);
}

static size_t	count_new_line(char *str)
{
	size_t	new_line_count;

	new_line_count = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			new_line_count++;
		}
		str++;
	}
	return (new_line_count);
}

static void	count_map_height(const char *filename, t_map *map)
{
	char	read_buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	size_t	new_line_count;
	int		fd;

	new_line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			perror("File read failed");
			exit(EXIT_FAILURE);
		}
		if (bytes_read == 0)
		{
			new_line_count += check_last_char(read_buffer);
			break ;
		}
		read_buffer[bytes_read] = '\0';
		new_line_count += count_new_line(read_buffer);
	}
	close(fd);
	map->height = new_line_count;
}

t_map	init_map(void)
{
	t_map	map;

	map->height = 0;
	map->width = 0;
	map->max_z = 0;
	map->min_z = 0;
	map->grids = NULL;
	return (map);
}

static bool	check_file_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	int		result;

	if (!filename || !extension)
	{
		return (false);
	}
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
	{
		return (false);
	}
	result = ft_strcasecmp(&filename[filename_len - extension_len], extension);
	return (result == 0);
}

static void	check_args(int argc, const char *argv[])
{
	if (argc != 2)
	{
		print_error_exit(ERR_ARGC);
	}
	if (!check_file_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_FILE_EXT);
	}
}

int	main(int argc, const char *argv[])
{
	t_map	map;
	t_point	**points;

	check_args(argc, argv);
	count_map_height(argv[1], &map);
	open_file(argv[1]);
	printf("Hello, world!\n");
	return (0);
}
