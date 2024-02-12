/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:22:53 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/11 01:15:30 by sakitaha         ###   ########.fr       */
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

/**
 * mlx_expose_hookの使い方がわからないので検索したら、キーやループなどと一緒にフックとして記述。
第ニ引数には何を入れるのか悩んで調べたところ、mlx_put_image_to_windowを使って画面を描写する関数をコピペしたものを作成してその関数名を入れ、画面描写関数はvoidで作成していたのでintにして最後にreturn (0);を追記したところ対応できました。 (編集済) Based on discord
 */

int	expose_hook(t_fdf *fdf)
{
	// TODO: shuould I use render_func()?
	//mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img, 0, 0);
	//TODO: What is the return value?
	return (0);
}

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

//------

void	close_window(t_fdf *fdf)
{
	free_mlx_ptr(fdf);
	free_point_matrix(fdf->points, fdf->max_y);
}

/**
 * Based on keysym defined in /opt/X11/include/X11/keysymdef.h
 *
  */

//TODO : Later to delete debug printf
int	key_hook(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		close_window(fdf);
		exit(0);
	}
	if (keysym == XK_Up || keysym == XK_w || keysym == XK_W)
	{
		printf("The %d key (W) or up arrow has been pressed\n\n", keysym);
		color_screen(fdf, encode_rgb(0, 255, 0));
	}
	else if (keysym == XK_Left || keysym == XK_a || keysym == XK_A)
	{
		printf("The %d key (A) or left arrow has been pressed\n\n", keysym);
		color_screen(fdf, encode_rgb(255, 0, 0));
	}
	else if (keysym == XK_Down || keysym == XK_s || keysym == XK_S)
	{
		printf("The %d key (S) or down arrow has been pressed\n\n", keysym);
		color_screen(fdf, encode_rgb(0, 255, 0));
	}
	else if (keysym == XK_Right || keysym == XK_d || keysym == XK_D)
	{
		printf("The %d key (D) or right arrow has been pressed\n\n", keysym);
		color_screen(fdf, encode_rgb(0, 0, 255));
	}
	else
	{
		printf("The %d key has been pressed\n\n", keysym);
		color_screen(fdf, encode_rgb(0, 0, 0));
	}
	//mlx_put_image_to_window(fdf->xvar, fdf->window, fdf->img, 0, 0);
	return (0);
}
