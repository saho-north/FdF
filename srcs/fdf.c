/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/22 22:44:44 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	is_valid_after_minus(const char *str)
{
	while (*str == '0')
		str++;
	if (!ft_isdigit(*str))
		return (false);
	return (true);
}
// 8,0xFFFFFF

static bool	check_split_line(const char *str)
{
	while (*str)
	{
		if (*str == '-' && is_valid_after_minus(str + 1))
		{
			str++;
		}
		if (!ft_isdigit(*str))
		{
			return (false);
		}
		while (ft_isidigit(*str))
		{
			str++;
		}
		if (*str == '\0')
		{
			break ;
		}
		if (*str != ',' || *str != '0' ||)
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

void	assign_point(char **split_line, t_env *env, size_t x, size_t y)
{
	t_point	*point;
	char	*str;
	bool	is_valid_z;
	char	**inputs;

	check_split_line(split_line[x]);
	point = &env->points[y][x];
	point->source_z = ft_atoi_endptr(split_line[x], is_valid_z);
	str = ft_itoa(point->source_z);
	if (ft_strncmp(str, split_line[x], ft_strlen(str)) != 0)
	{
		free(str);
		free_split_line(split_line);
		free_point_matrix(env->points, env->max_y);
		print_error_exit(ERR_MAP);
	}
	point->x = (float)x;
	point->y = (float)y;
	point->z = (float)point->source_z;
	if (point->z > env->max_z)
		env->max_z = point->z;
	if (point->z < env->min_z)
		env->min_z = point->z;
}

void	parse_line(const char *line, t_env *env, size_t current_y)
{
	size_t	current_x;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		free(line);
		free_point_matrix(env->points, current_y);
		print_error_exit(ERR_MALLOC);
	}
	current_x = 0;
	while (split_line[current_x] && current_x < env->max_x)
	{
		assign_point(env, current_x, current_y, ft_atoi(split_line[current_x]));
		current_x++;
	}
	free_split_line(split_line);
}

void	read_map_file(const char *filename, t_env *env)
{
	t_gnl_res	res;
	int			fd;
	size_t		current_y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_point_matrix(env->points, env->max_y);
		perror_exit(ERR_FILE_OPEN);
	}
	current_y = 0;
	while (current_y < env->max_y)
	{
		res = get_next_line(fd);
		if (res.line_status == LINE_ERROR || !res.line)
		{
			close(fd);
			free_point_matrix(env->points, env->max_y);
			print_error_exit(ERR_READ_LINE);
		}
		parse_line(res.line, env, current_y);
		free(res.line);
		res.line = NULL;
		current_y++;
	}
	close(fd);
}

static void	init_point_matrix(t_env *env)
{
	size_t	y;

	env->points = (t_point **)ft_calloc(env->max_y, sizeof(t_point *));
	if (!env->points)
	{
		print_error_exit(ERR_MALLOC);
	}
	y = 0;
	while (y < env->max_y)
	{
		env->points[y] = (t_point *)ft_calloc(env->max_x, sizeof(t_point));
		if (!env->points[y])
		{
			free_point_matrix(env->points, y);
			print_error_exit(ERR_MALLOC);
		}
		y++;
	}
}

static void	init_env_struct(t_env *env)
{
	// t_envの変数が増えたら、初期化の中身も後で増やす
	env->points = NULL;
	env->max_x = 0;
	env->max_y = 0;
	env->max_z = INT_MIN;
	env->min_z = INT_MAX;
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

int	main(int argc, const char *argv[])
{
	t_env	env;

	if (argc != 2 || !check_file_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_ARG);
	}
	init_env_struct(&env);
	get_map_size(argv[1], &env);
	init_point_matrix(&env);
	//以下は未整理の部分
	read_map_file(argv[1], &env);
	// printf("Hello, world!\n");
	// void *mlx;     //display
	// void *mlx_win; //window
	// t_data image;  //image
	// mlx = mlx_init();
	// //display init
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!"); //window init
	// image.img = mlx_new_image(mlx, 1920, 1080);                //image init
	return (0);
}
