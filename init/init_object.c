/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:39:24 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 10:39:24 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>

void	init_coord(t_vec *vec, char *value, t_all *all)
{
	char	**args;

	args = ft_split(value, ',', all);
	if (!args || args[3] != NULL)
		print_error("invalid coord argument size", all);
	vec->x = ft_atof(args[0], 'e', all);
	vec->y = ft_atof(args[1], 'e', all);
	vec->z = ft_atof(args[2], 'e', all);
}

void	init_vector(t_vec *vec, char *value, t_all *all)
{
	char	**args;

	args = ft_split(value, ',', all);
	if (!args || args[3] != NULL)
		print_error("invalid vector argument size", all);
	vec->x = ft_atof(args[0], 'v', all);
	vec->y = ft_atof(args[1], 'v', all);
	vec->z = ft_atof(args[2], 'v', all);
}

void	init_sphere(char **args, t_all *all)
{
	int			rgb[3];
	t_sphere	*new_sphere;

	if (args[4] != NULL || args[3] == NULL)
		print_error("invalid sphere argument size", all);
	new_sphere = (t_sphere *)safe_malloc(sizeof(t_sphere), all);
	init_coord(&new_sphere->center, args[1], all);
	new_sphere->radius = ft_atof(args[2], 'e', all) / 2.0;
	init_rgb(rgb, args[3], all);
	new_sphere->color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	new_sphere->next = all->sphere;
	all->sphere = new_sphere;
}

void	init_plane(char **args, t_all *all)
{
	int		rgb[3];
	t_plane	*new_plane;

	if (args[4] != NULL || args[3] == NULL)
		print_error("invalid plane argument size", all);
	new_plane = (t_plane *)safe_malloc(sizeof(t_plane), all);
	init_coord(&new_plane->point, args[1], all);
	init_vector(&new_plane->normal, args[2], all);
	init_rgb(rgb, args[3], all);
	new_plane->color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	new_plane->next = all->plane;
	all->plane = new_plane;
}

void	init_cylinder(char **args, t_all *all)
{
	int			rgb[3];
	t_cylinder	*new_cylinder;

	if (args[6] != NULL || args[5] == NULL)
		print_error("invalid cylinder argument size", all);
	new_cylinder = (t_cylinder *)safe_malloc(sizeof(t_cylinder), all);
	init_coord(&new_cylinder->center, args[1], all);
	init_vector(&new_cylinder->axis, args[2], all);
	new_cylinder->axis = vec_norm(new_cylinder->axis);
	new_cylinder->diam = ft_atof(args[3], 'e', all);
	new_cylinder->height = ft_atof(args[4], 'e', all);
	init_rgb(rgb, args[5], all);
	new_cylinder->color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	new_cylinder->next = all->cylinder;
	all->cylinder = new_cylinder;
}
