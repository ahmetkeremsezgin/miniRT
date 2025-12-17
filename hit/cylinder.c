/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:15:03 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 14:40:32 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static int	check_height(t_cylinder *cy, t_ray *ray, double t)
{
	t_vec	hit_point;
	t_vec	oc;
	double	hit_height;

	hit_point = vec_add(ray->origin, vec_mul(ray->dir, t));
	oc = vec_sub(hit_point, cy->center);
	hit_height = vec_dot(oc, cy->axis);
	if (fabs(hit_height) > (cy->height / 2.0))
		return (0);
	return (1);
}

static void	calc_coeffs(t_cylinder *cy, t_ray *ray, double *abc)
{
	t_vec	oc;
	double	dot_d_a;
	double	dot_oc_a;
	double	radius;

	oc = vec_sub(ray->origin, cy->center);
	dot_d_a = vec_dot(ray->dir, cy->axis);
	dot_oc_a = vec_dot(oc, cy->axis);
	radius = cy->diam / 2.0;
	abc[0] = vec_dot(ray->dir, ray->dir) - (dot_d_a * dot_d_a);
	abc[1] = 2 * (vec_dot(ray->dir, oc) - (dot_d_a * dot_oc_a));
	abc[2] = vec_dot(oc, oc) - (dot_oc_a * dot_oc_a) - (radius * radius);
}

double	hit_cylinder(t_cylinder *cy, t_ray *ray)
{
	double	abc[3];
	double	disc;
	double	t1;
	double	t2;

	calc_coeffs(cy, ray, abc);
	if (fabs(abc[0]) < 1e-6)
		return(-1.0);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (-1.0);
	disc = sqrt(disc);
	t1 = (-abc[1] - disc) / (2 * abc[0]);
	t2 = (-abc[1] + disc) / (2 * abc[0]);
	if (t1 > 0.001 && check_height(cy, ray, t1))
		return (t1);
	if (t2 > 0.001 && check_height(cy, ray, t2))
		return (t2);
	return (-1.0);
}
