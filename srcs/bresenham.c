/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:40:00 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/23 23:21:34 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	bresenham(int x1, int y1, int x2, int y2)
{
	int	m_new;
	int	slope_error_new;
	int	dx;
	int	y;

	dx = x2 - x1;
	m_new = 2 * (y2 - y1);
	slope_error_new = m_new - dx;
	y = y1;
	for (int x = x1; x <= x2; x++)
	{
		slope_error_new += m_new;
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * dx;
		}
	}
}
