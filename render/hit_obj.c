/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:42:34 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:49:30 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static void	check_spheres(t_sphere *sp, t_ray *ray, t_hit *rec)
{
	double	t;

	while (sp)
	{
		t = hit_sphere(sp, ray);
		if (t > 0.001 && t < rec->t)
		{
			rec->t = t;
			rec->type = OBJ_SPHERE;
			rec->obj = sp;
		}
		sp = sp->next;
	}
}

static void	check_planes(t_plane *pl, t_ray *ray, t_hit *rec)
{
	double	t;

	while (pl)
	{
		t = hit_plane(pl, ray);
		if (t > 0.001 && t < rec->t)
		{
			rec->t = t;
			rec->type = OBJ_PLANE;
			rec->obj = pl;
		}
		pl = pl->next;
	}
}

static void	check_cylinders(t_cylinder *cy, t_ray *ray, t_hit *rec)
{
	double	t;

	while (cy)
	{
		t = hit_cylinder(cy, ray);
		if (t > 0.001 && t < rec->t)
		{
			rec->t = t;
			rec->type = OBJ_CYLINDER;
			rec->obj = cy;
		}
		cy = cy->next;
	}
}

void	get_closest_obj(t_all *all, t_ray *ray, t_hit *rec)
{
	check_spheres(all->sphere, ray, rec);
	check_planes(all->plane, ray, rec);
	check_cylinders(all->cylinder, ray, rec);
}
