/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:40:07 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/20 01:22:03 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * hooks.c:
 * - give instructions to interact with the mouse and keyboard
 */
/*
** "mlx.h" for mlx_hook()
** "fdf.h" for key_press(), close(), mouse_press(), mouse_release() and
** mouse_move()
** <stdlib.h> for exit()
*/

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

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
