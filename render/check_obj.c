/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:36:49 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/18 14:26:57 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static int	check_spheres(t_sphere *sp, t_ray *ray, double dist)
{
	while (sp)
	{
		if (check_obstacle(hit_sphere(sp, ray), dist))
			return (1);
		sp = sp->next;
	}
	return (0);
}

static int	check_planes(t_plane *pl, t_ray *ray, double dist)
{
	while (pl)
	{
		if (check_obstacle(hit_plane(pl, ray), dist))
			return (1);
		pl = pl->next;
	}
	return (0);
}

static int	check_cylinders(t_cylinder *cy, t_ray *ray, double dist)
{
	while (cy)
	{
		if (check_obstacle(hit_cylinder(cy, ray), dist))
			return (1);
		cy = cy->next;
	}
	return (0);
}

int	is_in_shadow(t_all *all, t_vec hit_point, t_vec light_dir, double l_dist)
{
	t_ray	shadow_ray;

	shadow_ray.origin = hit_point;
	shadow_ray.dir = light_dir;
	if (check_spheres(all->sphere, &shadow_ray, l_dist))
		return (1);
	if (check_planes(all->plane, &shadow_ray, l_dist))
		return (1);
	if (check_cylinders(all->cylinder, &shadow_ray, l_dist))
		return (1);
	return (0);
}
