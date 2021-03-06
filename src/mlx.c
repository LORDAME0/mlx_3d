/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:52:58 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:38:13 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_mlx	get_mlx_info(t_mlx *mlx)
{
	static t_mlx	static_mlx;

	if (mlx)
		static_mlx = *mlx;
	return (static_mlx);
}

void	start(void)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_loop(m.mlx);
}

win_ptr	init_win(mlx_ptr mlx, t_res resolution, char *title)
{
	win_ptr	win;

	if (mlx == NULL)
	{
		perror("Error ");
		exit(1);
	}
	win = mlx_new_window(mlx, resolution.width,
			resolution.height, title);
	if (win == NULL)
	{
		perror("Error ");
		exit(1);
	}
	return (win);
}

t_mlx	init(t_res resolution, char *title)
{
	t_mlx	mlx_info;
	mlx_ptr	mlx;
	win_ptr	win;

	mlx = mlx_init();
	win = init_win(mlx, resolution, title);
	mlx_info = (t_mlx){
		.mlx = mlx,
		.win = win,
		.resolution = resolution,};
	get_mlx_info(&mlx_info);
	return (mlx_info);
}

int	make_color(t_rgb c, float alpha)
{
	t_color	color;

	c.blue = clamp(c.blue, 0, 1);
	c.green = clamp(c.green, 0, 1);
	c.red = clamp(c.red, 0, 1);
	color.blue = c.blue * 255.0;
	color.green = c.green * 255.0;
	color.red = c.red * 255.0;
	color.alpha = alpha * 255.0;
	return (color.color);
}
