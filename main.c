/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:47:39 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:47:39 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "./mini_rt.h"
#include "./minilibx_linux/mlx.h"

int setup_arg(char *filename, t_all *all)
{
    int		fd;
    char	*line;
	char	**args;

    fd = open(filename, O_RDONLY);
    while (1)
    {
		line = get_next_line(fd);
		if(line == NULL)
			return (1);
        if(line[0] == '\n')
        {
            free(line);
            continue ;
        }
        line = collector_dup(line, all);
        args = ft_split(line, ' ', all);
        init_data(args, all);
    }
}

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void visualize(t_all *all)
{
    int         x;
    int         y;
    t_ray       ray;
    t_vec       pixel_center;
    int         color;
    t_camera    *cam;

    cam = all->camera;
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            t_vec p_x = vec_mul(cam->pixel_delta_u, (double)x);
            t_vec p_y = vec_mul(cam->pixel_delta_v, (double)y);
            pixel_center = vec_add(cam->upper_left, vec_add(p_x, p_y));
            ray.origin = cam->origin;
            ray.dir = vec_sub(pixel_center, cam->origin);
            ray.dir = vec_norm(ray.dir);
            color = trace_ray(all, &ray);
            put_pixel(&all->mlx.img, x, y, color);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(all->mlx.mlx, all->mlx.mlx_win, all->mlx.img.img, 0, 0);
}

int main(int ac, char **av)
{
    t_all all;

    all = (t_all){0};
    file_check(ac, av);
    setup_arg(av[1], &all);
    setup_camera(&all);
    init_mlx(&all);
    visualize(&all);
    print_all(&all);
    mlx_loop(all.mlx.mlx);
    return (0);
}