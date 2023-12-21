/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/21 16:17:07 by sakitaha         ###   ########.fr       */
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

// t_envの変数が増えたら、初期化の中身も後で増やすこと
static void	init_env_struct(t_env *env)
{
	env->points = NULL;
	env->max_x = 0;
	env->max_y = 0;
	env->max_z = 0;
	env->min_z = 0;
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
	t_env	env;

	check_args(argc, argv);
	init_env_struct(&env);
	get_map_size(argv[1], &env);
	open_file(argv[1]);
	//以下は未整理の部分
	printf("Hello, world!\n");
	void *mlx;     //display
	void *mlx_win; //window
	t_data image;  //image
	mlx = mlx_init();
	//display init
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!"); //window init
	image.img = mlx_new_image(mlx, 1920, 1080);                //image init
	return (0);
}
