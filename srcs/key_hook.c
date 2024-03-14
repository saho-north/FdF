/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 01:17:37 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 17:07:04 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

/**
 * Handle key press event
 */
int	key_press(int key, t_fdf *fdf)
{
	if (key == XK_Shift_L || key == XK_Shift_R)
	{
		fdf->is_shift_pressed = true;
		return (0);
	}
	handle_simple_actions(key, fdf);
	handle_projection(key, fdf);
	handle_movement(key, fdf);
	handle_rotation(key, fdf);
	handle_scale(key, fdf);
	return (0);
}

/**
 * Handle key release event
 */
int	key_release(int key, t_fdf *fdf)
{
	if (key == XK_Shift_L || key == XK_Shift_R)
	{
		fdf->is_shift_pressed = false;
		return (0);
	}
	return (0);
}
