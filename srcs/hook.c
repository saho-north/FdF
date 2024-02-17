/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:22:53 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/16 12:47:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

/*
TODO: 以下の関数を実装する

モデルの平行移動
    マウス: ドラッグ＆ドロップ操作により、モデルを自由に移動できるようにします。例えば、マウスの左ボタンを押しながら移動することでモデルを平行移動させることができます。

モデルの回転
    マウス: マウスの右ボタンを押しながらドラッグすることで、モデルを回転させることができます。マウス移動の方向と距離に応じて回転角度を調整します。

TODO: depth_scaleを変更する関数を実装する
 */

int	button_press(int button, int x, int y, t_fdf *fdf)
{
	printf("Buttonpress: %d\n", button);
	if (button == Button1)
	{
		printf("Left mouse button pressed at (%d, %d)!\n", x, y);
		// TODO: Later to implement the translate function
	}
	else if (button == Button3)
	{
		printf("Right mouse button pressed at (%d, %d)!\n", x, y);
		// TODO: Later to implement the translate function
	}
	else if (button == Button4)
	{
		fdf->scale++;
	}
	else if (button == Button5 && fdf->scale - 1 > 0)
	{
		fdf->scale--;
	}
	fdf->needs_redraw = true;
	return (0);
}

int	button_release(int button, int x, int y, t_fdf *fdf)
{
	(void)button;
	(void)x;
	(void)y;
	(void)fdf;
	printf("Buttonrelease: %d\n", button);
	// if (button == Button1)
	// {
	// 	printf("Left mouse button pressed at (%d, %d)!\n", x, y);
	// 	// TODO: Later to implement the translate function
	// }
	// else if (button == Button3)
	// {
	// 	printf("Right mouse button pressed at (%d, %d)!\n", x, y);
	// 	// TODO: Later to implement the translate function
	// }
	// else if (button == Button4)
	// {
	// 	fdf->scale++;
	// }
	// else if (button == Button5 && fdf->scale - 1 > 0)
	// {
	// 	fdf->scale--;
	// }
	fdf->needs_redraw = true;
	return (0);
}

int	handle_loop_hook(t_fdf *fdf)
{
	if (!fdf->needs_redraw)
	{
		return (0);
	}
	render(fdf);
	return (0);
}
