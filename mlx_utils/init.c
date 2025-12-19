/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:46:13 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:16:05 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include "../minilibx_linux/mlx.h"
#include <stdlib.h>

int	close_window(t_all *all)
{
	mlx_destroy_image(all->mlx.mlx, all->mlx.img.img);
	mlx_destroy_window(all->mlx.mlx, all->mlx.mlx_win);
	mlx_destroy_display(all->mlx.mlx);
	free(all->mlx.mlx);
	clean_collector(all);
	return (0);
}

int	key_hook(int keycode, t_all *all)
{
	if (keycode == 65307)
		close_window(all);
	return (0);
}

void	init_mlx(t_all *all)
{
	all->mlx.mlx = mlx_init();
	all->mlx.mlx_win = mlx_new_window(all->mlx.mlx, WIDTH, HEIGHT, "!MiniRT!");
	all->mlx.img.img = mlx_new_image(all->mlx.mlx, WIDTH, HEIGHT);
	all->mlx.img.addr = mlx_get_data_addr(all->mlx.img.img,
			&all->mlx.img.bits_per_pixel,
			&all->mlx.img.line_length, &all->mlx.img.endian);
	mlx_key_hook(all->mlx.mlx_win, key_hook, all);
	mlx_hook(all->mlx.mlx_win, 17, 0, close_window, all);
}
