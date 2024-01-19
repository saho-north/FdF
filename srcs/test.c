/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 21:10:39 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/19 21:10:39 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	parse_line(const char *line, t_fdf *fdf, size_t y)
// {
// 	size_t	x;
// 	char	**split_line;

// 	split_line = ft_split(line, ' ');
// 	if (!split_line)
// 	{
// 		free(line);
// 		free_point_matrix(fdf->points, y);
// 		print_error_exit(ERR_MALLOC);
// 	}
// 	x = 0;
// 	while (split_line[x] && x < fdf->max_x)
// 	{
// 		if (!parse_point_input(split_line[x], fdf, x, y))
// 		{
// 			//これでいいかよくわからないから後でチェックする
// 			free_split_line(split_line);
// 			free_point_matrix(fdf->points, fdf->max_y);
// 			print_error_exit(ERR_MAP);
// 		}
// 		x++;
// 	}
// 	free_split_line(split_line);
// }

// void	read_map_file(const char *filename, t_fdf *fdf)
// {
// 	t_gnl_res	res;
// 	int			fd;
// 	size_t		y;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		free_point_matrix(fdf->points, fdf->max_y);
// 		perror_exit(ERR_FILE_OPEN);
// 	}
// 	y = 0;
// 	while (y < fdf->max_y)
// 	{
// 		res = get_next_line(fd);
// 		if (res.line_status == LINE_ERROR || !res.line)
// 		{
// 			close(fd);
// 			free_point_matrix(fdf->points, fdf->max_y);
// 			print_error_exit(ERR_READ_LINE);
// 		}
// 		parse_line(res.line, fdf, y);
// 		free(res.line);
// 		res.line = NULL;
// 		y++;
// 	}
// 	close(fd);
// }

// int	button_press(int button, int x, int y, t_fdf *fdf)
// {
// 	if (button == 1)
// 		printf("Left mouse button pressed at (%d, %d)!\n", x, y);
// 	else if (button == 3)
// 		printf("Right mouse button pressed at (%d, %d)!\n", x, y);
// 	return (0);
// }

// int	change_color(t_fdf *fdf)
// {
// 	// Fill the window with the current color
// 	//  mlx_clear_window(fdf->mlx, fdf->win);
// 	mlx_string_put(fdf->xvar, fdf->window, 150, 150, fdf->color,
// 			"Color Changing Window!");
// 	// Cycle through some basic colors: RED, GREEN, BLUE
// 	if (fdf->color == 0xFF0000)      // If it's red
// 		fdf->color = 0x00FF00;       // Change to green
// 	else if (fdf->color == 0x00FF00) // If it's green
// 		fdf->color = 0x0000FF;       // Change to blue
// 	else
// 		fdf->color = 0xFF0000; // Otherwise, go back to red
// 	return (0);
// }

// void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, unsigned int color)
// {
// 	char	*dst;

// 	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
// 	*(unsigned int *)dst = color;
// }

// void	color_screen(t_fdf *fdf, unsigned int color)
// {
// 	size_t	y;
// 	size_t	x;

// 	y = 0;
// 	while (y < fdf->height)
// 	{
// 		x = 0;
// 		while (x < fdf->width)
// 		{
// 			my_mlx_pixel_put(fdf, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// unsigned int	encode_rgb(unsigned char r, unsigned char g, unsigned char b)
// {
// 	return (r << 16 | g << 8 | b);
// }

// int	key_hook(int keycode, t_fdf *fdf)
// {
// 	if (keycode == 65307)
// 	{
// 		printf("The %d key (ESC) has been pressed\n\n", keycode);
// 		mlx_destroy_window(fdf->xvar, fdf->window);
// 		mlx_destroy_display(fdf->xvar);
// 		free(fdf->xvar);
// 		exit(1);
// 	}
// 	if (keycode == 97)
// 	{
// 		printf("The %d key (A) has been pressed\n\n", keycode);
// 		color_screen(fdf, encode_rgb(255, 0, 0));
// 	}
// 	else if (keycode == 115)
// 	{
// 		printf("The %d key (S) has been pressed\n\n", keycode);
// 		color_screen(fdf, encode_rgb(0, 255, 0));
// 	}
// 	else if (keycode == 100)
// 	{
// 		printf("The %d key (D) has been pressed\n\n", keycode);
// 		color_screen(fdf, encode_rgb(0, 0, 255));
// 	}
// 	else if (keycode == 119)
// 	{
// 		printf("The %d key (W) has been pressed\n\n", keycode);
// 		color_screen(fdf, encode_rgb(255, 255, 255));
// 	}
// 	else
// 	{
// 		printf("The %d key has been pressed\n\n", keycode);
// 		color_screen(fdf, encode_rgb(0, 0, 0));
// 	}
// 	mlx_put_image_to_window(fdf->xvar, fdf->window, fdf->img, 0, 0);
// 	return (0);
// }

// int	main(void)
// {
// 	t_fdf	fdf;

// 	fdf.xvar = mlx_init();
// 	if (!fdf.xvar)
// 	{
// 		write(1, "Error\n", 6);
// 		return (1);
// 	}
// 	fdf.width = 640;
// 	fdf.height = 480;
// 	fdf.name = "Hello, world!";
// 	fdf.window = mlx_new_window(fdf.xvar, fdf.width, fdf.height, fdf.name);
// 	if (!fdf.window)
// 	{
// 		write(1, "Error\n", 6);
// 		return (1);
// 	}
// 	fdf.img = mlx_new_image(fdf.xvar, fdf.width, fdf.height);
// 	if (!fdf.img)
// 	{
// 		mlx_destroy_window(fdf.xvar, fdf.window);
// 		mlx_destroy_display(fdf.xvar);
// 		free(fdf.xvar);
// 		write(1, "Error\n", 6);
// 		return (1);
// 	}
// 	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.stride, &fdf.endian);
// 	if (!fdf.addr)
// 	{
// 		mlx_destroy_image(fdf.xvar, fdf.img);
// 		mlx_destroy_window(fdf.xvar, fdf.window);
// 		mlx_destroy_display(fdf.xvar);
// 		free(fdf.xvar);
// 		write(1, "Error\n", 6);
// 		return (1);
// 	}
// 	printf("stride %d <-> width %d\n"
// 			"bpp %d\n"
// 			"endian %d\n",
// 			fdf.stride,
// 			fdf.width,
// 			fdf.bpp,
// 			fdf.endian);
// 	mlx_key_hook(fdf.window, key_hook, &fdf);
// 	mlx_mouse_hook(fdf.window, button_press, &fdf);
// 	mlx_loop_hook(fdf.xvar, change_color, &fdf);
// 	mlx_loop(fdf.xvar);
// 	/*
// 	mlx_destroy_window(xvar, mlx_window);
// 	mlx_destroy_display(xvar);
// 	free(xvar);
// 	*/
// 	return (0);
// }
