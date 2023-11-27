/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/27 17:59:42 by sakitaha         ###   ########.fr       */
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
	int				fd;
	const char		*line;
	size_t			i;
	int				fd;
	char			*line;
	t_read_status	status;
	char			command[1024];

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
	// ---
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd, &status);
		if (status == READ_ERROR)
		{
			fprintf(stderr, "Error reading line.\n");
			break ;
		}
		if (line == NULL)
		{
			if (status == READ_EOF)
			{
				printf("End of file reached.\n");
			}
			break ;
		}
		printf("Read line: %s", line);
		free(line);
	}
	close(fd);
	sprintf(command, "leaks %d", getpid());
	system(command);
	return (0);
}

static bool	check_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	size_t	extension_index;
	size_t	i;
	char	file_extension[256];
	char	expected_extension[256];

	if (!filename || !extension)
		return (false);
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
		return (false);
	extension_index = filename_len - extension_len;
	i = 0;
	while (i < extension_len)
	{
		file_extension[i] = ft_tolower(filename[extension_index + i]);
		expected_extension[i] = ft_tolower(extension[i]);
		i++;
	}
	file_extension[4] = '\0';
	return (ft_strncmp(file_extension, expected_extension, extension_len) == 0);
}

static bool	check_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	size_t	extension_index;
	size_t	i;
	char	file_extension[32];
	char	expected_extension[32];

	if (!filename || !extension)
		return (false);
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
		return (false);
	extension_index = filename_len - extension_len;
	i = 0;
	while (i < extension_len)
	{
		file_extension[i] = ft_tolower(filename[extension_index + i]);
		expected_extension[i] = ft_tolower(extension[i]);
		i++;
	}
	file_extension[extension_len] = '\0';
	expected_extension[extension_len] = '\0';
	return (ft_strncmp(file_extension, expected_extension, extension_len) == 0);
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
