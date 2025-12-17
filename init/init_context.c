/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:46:36 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:46:36 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>

void	init_rgb(int *rgb, char *value, t_all *all)
{
	char	**args;

	args = ft_split(value, ',', all);
	if (!args || args[3] != NULL)
		print_error("invalid argument size", all);
	rgb[0] = ft_atoi(args[0], 'c', all);
	rgb[1] = ft_atoi(args[1], 'c', all);
	rgb[2] = ft_atoi(args[2], 'c', all);
}

void	init_ambient(char **args, t_all *all)
{
	int	rgb[3];

	if (all->ambient != NULL)
		print_error("too many ambient size", all);
	if (args[3] != NULL)
		print_error("invalid argument size", all);
	all->ambient = (t_ambient *)safe_malloc(sizeof(t_ambient), all);
	all->ambient->ratio = ft_atof(args[1], 'r', all);
	init_rgb(rgb, args[2], all);
	all->ambient->red = rgb[0];
	all->ambient->green = rgb[1];
	all->ambient->blue = rgb[2];
}

void	init_camera(char **args, t_all *all)
{
	if (all->camera != NULL)
		print_error("too many camera definition", all);
	if (args[4] != NULL)
		print_error("invalid camera argument size", all);
	all->camera = (t_camera *)safe_malloc(sizeof(t_camera), all);
	init_coord(&all->camera->origin, args[1], all);
	init_vector(&all->camera->dir, args[2], all);
	all->camera->fov = ft_atoi(args[3], 'd', all);
}

void	init_light(char **args, t_all *all)
{
	int	rgb[3];

	if (all->light != NULL)
		print_error("too many light definition", all);
	if (args[4] != NULL)
		print_error("invalid light argument size", all);
	all->light = (t_light *)safe_malloc(sizeof(t_light), all);
	init_coord(&all->light->center, args[1], all);
	all->light->brightness = ft_atof(args[2], 'b', all);
	init_rgb(rgb, args[3], all);
	all->light->color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void	init_data(char **line, t_all *all)
{
	if (ft_strcmp(line[0], "A") == 0)
		init_ambient(line, all);
	else if (ft_strcmp(line[0], "C") == 0)
		init_camera(line, all);
	else if (ft_strcmp(line[0], "L") == 0)
		init_light(line, all);
	else if (ft_strcmp(line[0], "sp") == 0)
		init_sphere(line, all);
	else if (ft_strcmp(line[0], "pl") == 0)
		init_plane(line, all);
	else if (ft_strcmp(line[0], "cy") == 0)
		init_cylinder(line, all);
	else
		print_error("invalid element name", all);
}
