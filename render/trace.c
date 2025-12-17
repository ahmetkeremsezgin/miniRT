/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:34:03 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:49:10 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static void	get_normal_color(t_hit *rec, t_vec p, t_vec *n, int *c)
{
	t_cylinder	*cyl;
	t_vec		oc;
	double		dot;

	if (rec->type == OBJ_SPHERE)
	{
		*n = vec_norm(vec_sub(p, ((t_sphere *)rec->obj)->center));
		*c = ((t_sphere *)rec->obj)->color;
	}
	else if (rec->type == OBJ_PLANE)
	{
		*n = ((t_plane *)rec->obj)->normal;
		*c = ((t_plane *)rec->obj)->color;
	}
	else if (rec->type == OBJ_CYLINDER)
	{
		cyl = (t_cylinder *)rec->obj;
		oc = vec_sub(p, cyl->center);
		dot = vec_dot(cyl->axis, oc);
		*n = vec_norm(vec_sub(oc, vec_mul(cyl->axis, dot)));
		*c = cyl->color;
	}
}

int	trace_ray(t_all *all, t_ray *ray)
{
	t_hit	rec;
	t_vec	hit_point;
	t_vec	normal;
	int		color;

	rec.t = 1.0 / 0.0;
	rec.type = OBJ_NONE;
	rec.obj = NULL;
	get_closest_obj(all, ray, &rec);
	if (rec.type == OBJ_NONE)
		return (0x000000);
	hit_point = vec_add(ray->origin, vec_mul(ray->dir, rec.t));
	get_normal_color(&rec, hit_point, &normal, &color);
	if (vec_dot(ray->dir, normal) > 0)
		normal = vec_mul(normal, -1);
	hit_point = vec_add(hit_point, vec_mul(normal, 0.0001));
	all->camera->cam_view_dir = vec_norm(vec_mul(ray->dir, -1.0));
	return (compute_lighting(all, hit_point, normal, color));
}
