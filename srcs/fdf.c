/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 05:50:30 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/23 22:16:13 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_line(const char *line, t_env *env, size_t y)
{
	size_t	x;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		free(line);
		free_point_matrix(env->points, y);
		print_error_exit(ERR_MALLOC);
	}
	x = 0;
	while (split_line[x] && x < env->max_x)
	{
		if (!parse_point_input(split_line[x], env, x, y))
		{
			//これでいいかよくわからないから後でチェックする
			free_split_line(split_line);
			free_point_matrix(env->points, env->max_y);
			print_error_exit(ERR_MAP);
		}
		x++;
	}
	free_split_line(split_line);
}

void	read_map_file(const char *filename, t_env *env)
{
	t_gnl_res	res;
	int			fd;
	size_t		y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_point_matrix(env->points, env->max_y);
		perror_exit(ERR_FILE_OPEN);
	}
	y = 0;
	while (y < env->max_y)
	{
		res = get_next_line(fd);
		if (res.line_status == LINE_ERROR || !res.line)
		{
			close(fd);
			free_point_matrix(env->points, env->max_y);
			print_error_exit(ERR_READ_LINE);
		}
		parse_line(res.line, env, y);
		free(res.line);
		res.line = NULL;
		y++;
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
