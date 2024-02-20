/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 01:17:37 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/20 18:15:01 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/keysym.h>

//TODO: depth_scaleを変更する関数を実装する

int	key_press(int key, t_fdf *fdf)
{
	if (key == XK_Escape)
	{
		clean_exit(fdf);
	}
	else if (key == XK_r)
	{
		fdf->projection = ISOMETRIC;
		reset_render_param(fdf);
	}
	else if (key == XK_0)
	{
		fdf->projection = ISOMETRIC;
	}
	else if (key == XK_1)
	{
		fdf->projection = ORTHOGRAPHIC;
	}
	else if (key == XK_2)
	{
		fdf->projection = OBLIQUE;
	}
	else if (key == XK_3)
	{
		fdf->projection = CAVALIER;
	}
	return (0);
}

static void	handle_scale(int key, t_fdf *fdf)
{
	if (key == XK_plus)
	{
		fdf->scale++;
	}
	else if (key == XK_minus && fdf->scale - 1 > 0)
	{
		fdf->scale--;
	}
}

static void	handle_movement(int key, t_fdf *fdf)
{
	if (key == XK_Up)
	{
		fdf->y_move -= MOVE_STEP;
	}
	else if (key == XK_Left)
	{
		fdf->x_move -= MOVE_STEP;
	}
	else if (key == XK_Down)
	{
		fdf->y_move += MOVE_STEP;
	}
	else if (key == XK_Right)
	{
		fdf->x_move += MOVE_STEP;
	}
}

static void	handle_rotation(int key, t_fdf *fdf)
{
	if (key == XK_w)
	{
		fdf->x_degree += ROTATE_STEP;
	}
	else if (key == XK_s)
	{
		fdf->x_degree -= ROTATE_STEP;
	}
	else if (key == XK_a)
	{
		fdf->y_degree += ROTATE_STEP;
	}
	else if (key == XK_d)
	{
		fdf->y_degree -= ROTATE_STEP;
	}
	else if (key == XK_q)
	{
		fdf->z_degree += ROTATE_STEP;
	}
	else if (key == XK_e)
	{
		fdf->z_degree -= ROTATE_STEP;
	}
}

int	key_release(int key, t_fdf *fdf)
{
	if (key == XK_Up || key == XK_Left || key == XK_Down || key == XK_Right)
	{
		handle_movement(key, fdf);
	}
	else if (key == XK_w || key == XK_s || key == XK_a)
	{
		handle_rotation(key, fdf);
	}
	else if (key == XK_d || key == XK_q || key == XK_e)
	{
		handle_rotation(key, fdf);
	}
	else if (key == XK_plus || key == XK_minus)
	{
		handle_scale(key, fdf);
	}
	return (0);
}
