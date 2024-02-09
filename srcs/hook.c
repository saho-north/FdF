/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:22:53 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/08 20:46:00 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>

/**
 * hooks.c:
 * - give instructions to interact with the mouse and keyboard
 * - close the window
 * "mlx.h" for mlx_hook()
 * "fdf.h" for key_press(), close(), mouse_press(), mouse_release() and
 * mouse_move()
 * <stdlib.h> for exit()
 */

/*
int	mlx_hook(t_win_list *win, int x_event, int x_mask,
			int (*funct)(),void *param)
{
  win->hooks[x_event].hook = funct;
  win->hooks[x_event].param = param;
  win->hooks[x_event].mask = x_mask;
}

int	mlx_key_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[KeyRelease].hook = funct;
  win->hooks[KeyRelease].param = param;
  win->hooks[KeyRelease].mask = KeyReleaseMask;
}


int	mlx_loop_hook(t_xvar *xvar,int (*funct)(),void *param)
{
  xvar->loop_hook = funct;
  xvar->loop_param = param;
}


int	mlx_mouse_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[ButtonPress].hook = funct;
  win->hooks[ButtonPress].param = param;
  win->hooks[ButtonPress].mask = ButtonPressMask;
}
 */

void	close_window(t_fdf *fdf)
{
	free_mlx_ptr(fdf);
	free_point_matrix(fdf->points, fdf->max_y);
	exit(0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (key == 53)
		close_win(fdf);
	else if (key == 13 || key == 126)
		fdf->translation -= TRANS_FACTOR_X;
	else if (key == 1 || key == 125)
		fdf->translation += TRANS_FACTOR_X;
	else if (key == 0 || key == 123)
		fdf->alpha += 0.01;
	else if (key == 2 || key == 124)
		fdf->alpha -= 0.01;
	else if (key == 6)
		fdf->altitude += ALTITUDE;
	else if (key == 7)
		fdf->altitude -= ALTITUDE;
	if (keycode == 53)
		close_window(fdf);
	else if (keycode == 0 || keycode == 123)
		fdf->offset.x -= 10;
	else if (keycode == 2 || keycode == 124)
		fdf->offset.x += 10;
	else if (keycode == 1 || keycode == 125)
		fdf->offset.y += 10;
	else if (keycode == 13 || keycode == 126)
		fdf->offset.y -= 10;
	else
		ft_printf("%d\n", keycode);
	if (keycode == 65307)
	{
		printf("The %d key (ESC) has been pressed\n\n", keycode);
		close_window(fdf);
	}
	if (keycode == 97)
	{
		printf("The %d key (A) has been pressed\n\n", keycode);
		color_screen(fdf, encode_rgb(255, 0, 0));
	}
	else if (keycode == 115)
	{
		printf("The %d key (S) has been pressed\n\n", keycode);
		color_screen(fdf, encode_rgb(0, 255, 0));
	}
	else if (keycode == 100)
	{
		printf("The %d key (D) has been pressed\n\n", keycode);
		color_screen(fdf, encode_rgb(0, 0, 255));
	}
	else if (keycode == 119)
	{
		printf("The %d key (W) has been pressed\n\n", keycode);
		color_screen(fdf, encode_rgb(255, 255, 255));
	}
	else
	{
		printf("The %d key has been pressed\n\n", keycode);
		color_screen(fdf, encode_rgb(0, 0, 0));
	}
	mlx_put_image_to_window(fdf->xvar, fdf->window, fdf->img, 0, 0);
	return (0);
}

int	mouse_handler(int mousecode, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mousecode == 4 && fdf->scale - 1 > 0)
		fdf->scale--;
	if (mousecode == 5)
		fdf->scale++;
	return (0);
}

/*
** Close windowdow with 'X'
*/

int	close(void *param)
{
	(void)param;
	exit(0);
}

/*
** Connect functions-controllers to windowdow
*/

// void	setup_controls(t_fdf *fdf)
// {
// 	mlx_hook(fdf->window, 2, 0, key_press, fdf);
// 	mlx_hook(fdf->window, 17, 0, close, fdf);
// 	mlx_hook(fdf->window, 4, 0, mouse_press, fdf);
// 	mlx_hook(fdf->window, 5, 0, mouse_release, fdf);
// 	mlx_hook(fdf->window, 6, 0, mouse_move, fdf);
// }

int	button_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
		printf("Left mouse button pressed at (%d, %d)!\n", x, y);
	else if (button == 3)
		printf("Right mouse button pressed at (%d, %d)!\n", x, y);
	return (0);
}

int	change_color(t_fdf *fdf)
{
	// Fill the window with the current color
	//  mlx_clear_window(fdf->mlx, fdf->win);
	mlx_string_put(fdf->xvar, fdf->window, 150, 150, fdf->color,
			"Color Changing Window!");
	// Cycle through some basic colors: RED, GREEN, BLUE
	if (fdf->color == 0xFF0000)      // If it's red
		fdf->color = 0x00FF00;       // Change to green
	else if (fdf->color == 0x00FF00) // If it's green
		fdf->color = 0x0000FF;       // Change to blue
	else
		fdf->color = 0xFF0000; // Otherwise, go back to red
	return (0);
}

void	color_screen(t_fdf *fdf, unsigned int color)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			my_mlx_pixel_put(fdf, x, y, color);
			x++;
		}
		y++;
	}
}

unsigned int	encode_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

//-------------------------------------------------------------------

void	h_management(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_handler, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_handler, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_handler, fdf);
	//-------------------------------------------------------------------
	mlx_hook(fdf.win, 4, 0, mouse_handler, &fdf);
	mlx_hook(fdf.win, 2, 1L << 0, key_handler, &fdf);
	mlx_hook(fdf.win, 17, 1L << 0, close_window, &fdf);
}

int	key_handler(int key, t_fdf *fdf)
{
}

int	close_win(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
}

int	mouse_handler(int mousecode, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
		fdf->scale *= ZOOM_FACTOR;
	else if (mousecode == 5)
		fdf->scale /= ZOOM_FACTOR;
	return (0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
