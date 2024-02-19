/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 01:17:37 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/20 01:17:50 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/keysym.h>

/**
 * Handles the key press event.
 */
int	key_press(int keysym, t_fdf *fdf)
{
	printf("Keypress: %d\n", keysym);
	if (keysym == XK_Escape)
	{
		clean_exit(fdf);
	}
	else if (keysym == XK_0)
	{
		fdf->projection = ISOMETRIC;
	}
	else if (keysym == XK_1)
	{
		fdf->projection = ORTHOGRAPHIC;
	}
	else if (keysym == XK_2)
	{
		fdf->projection = OBLIQUE;
	}
	return (0);
}

static void	handle_scale(int keysym, t_fdf *fdf)
{
	if (keysym == XK_plus)
	{
		fdf->scale++;
	}
	else if (keysym == XK_minus && fdf->scale - 1 > 0)
	{
		fdf->scale--;
	}
}

static void	handle_movement(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Up)
	{
		fdf->y_move -= MOVE_STEP;
	}
	else if (keysym == XK_Left)
	{
		fdf->x_move -= MOVE_STEP;
	}
	else if (keysym == XK_Down)
	{
		fdf->y_move += MOVE_STEP;
	}
	else if (keysym == XK_Right)
	{
		fdf->x_move += MOVE_STEP;
	}
}

static void	handle_rotation(int keysym, t_fdf *fdf)
{
	if (keysym == XK_w)
	{
		fdf->x_degree += ROTATE_STEP;
	}
	else if (keysym == XK_s)
	{
		fdf->x_degree -= ROTATE_STEP;
	}
	else if (keysym == XK_a)
	{
		fdf->y_degree += ROTATE_STEP;
	}
	else if (keysym == XK_d)
	{
		fdf->y_degree -= ROTATE_STEP;
	}
	else if (keysym == XK_q)
	{
		fdf->z_degree += ROTATE_STEP;
	}
	else if (keysym == XK_e)
	{
		fdf->z_degree -= ROTATE_STEP;
	}
}
/**
 * Handles the key release event.
 * It changes the scale, movement, and rotation of the map.
 * It sets the flag to  the window.
 */
int	key_release(int keysym, t_fdf *fdf)
{
	if (keysym == XK_plus || keysym == XK_minus)
	{
		handle_scale(keysym, fdf);
	}
	else if (keysym == XK_Up || keysym == XK_Left || keysym == XK_Down
			|| keysym == XK_Right)
	{
		handle_movement(keysym, fdf);
	}
	else if (keysym == XK_w || keysym == XK_s || keysym == XK_a
			|| keysym == XK_d || keysym == XK_q || keysym == XK_e)
	{
		handle_rotation(keysym, fdf);
	}
	return (0);
}
