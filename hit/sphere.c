/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:01:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:57:11 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <math.h>

double	hit_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec	oc;
	double	abc[3];
	double	disc;
	double	t;

	oc = vec_sub(ray->origin, sp->center);
	abc[0] = vec_dot(ray->dir, ray->dir);
	abc[1] = 2.0 * vec_dot(oc, ray->dir);
	abc[2] = vec_dot(oc, oc) - (sp->radius * sp->radius);
	disc = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (-1.0);
	disc = sqrt(disc);
	t = (-abc[1] - disc) / (2.0 * abc[0]);
	if (t > 0.001)
		return (t);
	t = (-abc[1] + disc) / (2.0 * abc[0]);
	if (t > 0.001)
		return (t);
	return (-1.0);
}
