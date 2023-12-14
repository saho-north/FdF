/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kaiten.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 01:39:19 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/14 01:39:21 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

typedef struct
{
	double x, y, z;
}			Vector3D;

Vector3D	applyRotationX(Vector3D v, double angle)
{
	Vector3D	rotated;

	double rad = angle * M_PI / 180.0; // 角度をラジアンに変換
	rotated.x = v.x;
	rotated.y = v.y * cos(rad) - v.z * sin(rad);
	rotated.z = v.y * sin(rad) + v.z * cos(rad);
	return (rotated);
}

int	main(void)
{
	Vector3D	point;
	Vector3D	rotatedPoint;

	point = {1, 2, 3};
	rotatedPoint = applyRotationX(point, 10);
	printf("Rotated Point: x=%f, y=%f, z=%f\n", rotatedPoint.x, rotatedPoint.y,
			rotatedPoint.z);
	return (0);
}
