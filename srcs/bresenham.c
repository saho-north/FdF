/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 02:40:00 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/14 19:07:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	bresenham(int x1, int y1, int x2, int y2)
{
	int	m_new;
	int	slope_error_new;
	int	y;

	m_new = 2 * (y2 - y1);               // 線の傾きを2倍にする
	slope_error_new = m_new - (x2 - x1); //
	y = y1;
	for (int x = x1; x <= x2; x++)
	{
		printf("(%d, %d)\n", x, y);
		slope_error_new += m_new;
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * (x2 - x1);
		}
	}
}

/*

int	main(void)
{
	int	x1;

	x1 = 3, y1 = 2, x2 = 15, y2 = 5;
	bresenham(x1, y1, x2, y2);
	return (0);
}

 */
