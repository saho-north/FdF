/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liang_barsky.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:08:12 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 12:28:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	evaluate_clip_param(float p, float q, float *t0, float *t1)
{
	float	t;

	if (p == 0)
	{
		if (q < 0)
			return (false);
		return (true);
	}
	t = q / p;
	if (p < 0)
	{
		if (t > *t1)
			return (false);
		else if (t > *t0)
			*t0 = t;
	}
	else
	{
		if (t < *t0)
			return (false);
		else if (t < *t1)
			*t1 = t;
	}
	return (true);
}

static bool	clip_test(float p[], float q[])
{
	float	t0;
	float	t1;
	size_t	k;

	t0 = 0.0;
	t1 = 1.0;
	k = 0;
	while (k < 4)
	{
		if (!evaluate_clip_param(p[k], q[k], &t0, &t1))
		{
			return (false);
		}
		k++;
	}
	return (t0 <= t1);
}

bool	liang_barsky(t_point *point0, t_point *point1)
{
	int		dx;
	int		dy;
	float	p[4];
	float	q[4];

	dx = point1->x_2d - point0->x_2d;
	dy = point1->y_2d - point0->y_2d;
	p[0] = -dx;
	p[1] = dx;
	p[2] = -dy;
	p[3] = dy;
	q[0] = point0->x_2d;
	q[1] = WIN_WIDTH - 1 - point0->x_2d;
	q[2] = point0->y_2d;
	q[3] = WIN_HEIGHT - 1 - point0->y_2d;
	return (clip_test(p, q));
}
