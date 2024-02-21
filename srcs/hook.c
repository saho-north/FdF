/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:22:53 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 15:53:06 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

static void	handle_mouse_scale(int button, int x, int y, t_fdf *fdf)
{
	int	x_offset;
	int	y_offset;

	x_offset = (x - fdf->x_move) / fdf->scale;
	y_offset = (y - fdf->y_move) / fdf->scale;
	if (button == Button4)
	{
		fdf->scale += SCALE_STEP;
		fdf->x_move -= x_offset * SCALE_STEP;
		fdf->y_move -= y_offset * SCALE_STEP;
	}
	else if (button == Button5 && fdf->scale - 1 > 0)
	{
		fdf->scale -= SCALE_STEP;
		fdf->x_move += x_offset * SCALE_STEP;
		fdf->y_move += y_offset * SCALE_STEP;
	}
}

int	button_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == Button1)
	{
		fdf->mouse_press_x = x;
		fdf->mouse_press_y = y;
		fdf->is_mouse_dragging = true;
	}
	else if (button == Button4 || button == Button5)
	{
		handle_mouse_scale(button, x, y, fdf);
		fdf->redraw = true;
	}
	return (0);
}

int	motion_notify(int x, int y, t_fdf *fdf)
{
	if (fdf->is_mouse_dragging)
	{
		fdf->x_move += (x - fdf->mouse_press_x);
		fdf->y_move += (y - fdf->mouse_press_y);
		fdf->mouse_press_x = x;
		fdf->mouse_press_y = y;
		fdf->redraw = true;
	}
	return (0);
}

int	button_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	(void)fdf;
	if (button == Button1)
	{
		motion_notify(x, y, fdf);
		fdf->is_mouse_dragging = false;
	}
	return (0);
}

int	handle_loop_hook(t_fdf *fdf)
{
	if (fdf->redraw)
	{
		render(fdf);
		fdf->redraw = false;
	}
	return (0);
}
