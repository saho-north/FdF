/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:03:06 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 17:05:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

void	handle_simple_actions(int key, t_fdf *fdf)
{
	if (key == XK_Escape)
		clean_exit(fdf);
	else if (key == XK_r)
		reset_render_param(fdf);
	else if (key == XK_c)
		fdf->colorful = !fdf->colorful;
	else
		return ;
	fdf->redraw = true;
}

void	handle_projection(int key, t_fdf *fdf)
{
	if (key == XK_0)
		fdf->projection = ISOMETRIC;
	else if (key == XK_1)
		fdf->projection = ORTHOGRAPHIC;
	else if (key == XK_2)
		fdf->projection = CABINET;
	else if (key == XK_3)
		fdf->projection = TRIMETRIC;
	else
		return ;
	fdf->redraw = true;
}

void	handle_scale(int key, t_fdf *fdf)
{
	if (key == XK_plus || (fdf->is_shift_pressed && key == XK_equal))
		fdf->scale += SCALE_STEP;
	else if (key == XK_minus && fdf->scale - 1 > 0)
		fdf->scale -= SCALE_STEP;
	else if (key == XK_z)
		fdf->depth_scale += DEPTH_SCALE_STEP;
	else if (key == XK_x && fdf->depth_scale - 1 > 0)
		fdf->depth_scale -= DEPTH_SCALE_STEP;
	else
		return ;
	fdf->redraw = true;
}

void	handle_movement(int key, t_fdf *fdf)
{
	if (key == XK_Up)
		fdf->y_move -= MOVE_STEP;
	else if (key == XK_Left)
		fdf->x_move -= MOVE_STEP;
	else if (key == XK_Down)
		fdf->y_move += MOVE_STEP;
	else if (key == XK_Right)
		fdf->x_move += MOVE_STEP;
	else
		return ;
	fdf->redraw = true;
}

void	handle_rotation(int key, t_fdf *fdf)
{
	if (key == XK_w)
		fdf->x_degree += ROTATE_STEP;
	else if (key == XK_s)
		fdf->x_degree -= ROTATE_STEP;
	else if (key == XK_a)
		fdf->y_degree += ROTATE_STEP;
	else if (key == XK_d)
		fdf->y_degree -= ROTATE_STEP;
	else if (key == XK_q)
		fdf->z_degree += ROTATE_STEP;
	else if (key == XK_e)
		fdf->z_degree -= ROTATE_STEP;
	else
		return ;
	fdf->redraw = true;
}
