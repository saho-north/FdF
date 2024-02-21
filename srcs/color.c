/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:56:04 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 16:16:01 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	color1(int color_index)
{
	if (color_index == 8)
		return (PURE_GREEN);
	else if (color_index == 9)
		return (GREEN_CYAN);
	else if (color_index == 10)
		return (LIGHT_BLUE);
	else if (color_index == 11)
		return (CYAN);
	else if (color_index == 12)
		return (AQUA);
	else if (color_index == 13)
		return (BLUE);
	else if (color_index == 14)
		return (PURPLE);
	else if (color_index == 15)
		return (PINK);
	return (WHITE);
}

static int	color0(int color_index)
{
	if (color_index == 0)
		return (RED);
	else if (color_index == 1)
		return (RED_ORANGE);
	else if (color_index == 2)
		return (ORANGE);
	else if (color_index == 3)
		return (YELLOW_ORANGE);
	else if (color_index == 4)
		return (YELLOW);
	else if (color_index == 5)
		return (YELLOW_GREEN);
	else if (color_index == 6)
		return (LIGHT_GREEN);
	else if (color_index == 7)
		return (GREEN);
	return (WHITE);
}

int	get_color(t_fdf *fdf, t_point *p)
{
	int	color_index;

	if (!fdf->colorful || p->color != WHITE)
	{
		return (p->color);
	}
	color_index = (p->original_x + p->original_y) % 16;
	if (color_index < 8)
	{
		return (color0(color_index));
	}
	else
	{
		return (color1(color_index));
	}
}
