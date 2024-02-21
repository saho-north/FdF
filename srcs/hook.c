/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:22:53 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 12:17:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

// TODO: その場でscalingする
int	button_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == Button1)
	{
		fdf->mouse_press_x = x;
		fdf->mouse_press_y = y;
		fdf->is_mouse_dragging = true;
	}
	else if (button == Button4)
	{
		fdf->scale++;
		fdf->redraw = true;
	}
	else if (button == Button5 && fdf->scale - 1 > 0)
	{
		fdf->scale--;
		fdf->redraw = true;
	}
	return (0);
}

// CHECK: if I need to set redraw flag here

int	button_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	(void)fdf;
	if (button == Button1)
	{
		fdf->is_mouse_dragging = false;
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

int	handle_loop_hook(t_fdf *fdf)
{
	if (fdf->redraw)
	{
		render(fdf);
		fdf->redraw = false;
	}
	return (0);
}
