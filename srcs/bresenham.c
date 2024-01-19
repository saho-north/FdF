/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:40:00 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/24 08:32:28 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	bresenham(int x1, int y1, int x2, int y2)
{
	int	slope_error_new;
	int	m_new;
	int	dx;
	int	y;
	int	x;

	m_new = 2 * (y2 - y1);
	dx = x2 - x1;
	slope_error_new = m_new - dx;
	x = x1;
	y = y1;
	while (x <= x2)
	{
		printf("(%d, %d)\n", x, y);
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * dx;
		}
		slope_error_new += m_new;
		x++;
	}
}

void	bresenham(int x1, int y1, int x2, int y2)
{
	int	slope_error_new;
	int	m_new;
	int	dx;
	int	y;
	int	x;

	m_new = 2 * (y2 - y1);
	dx = x2 - x1;
	slope_error_new = m_new - dx;
	x = x1;
	y = y1;
	while (x <= x2)
	{
		printf("(%d, %d)\n", x, y);
		slope_error_new += m_new;
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * dx;
		}
		x++;
	}
}
