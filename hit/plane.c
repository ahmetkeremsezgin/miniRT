/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayilmaz <mayilmaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:15:25 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/11 15:28:09 by mayilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <math.h>

double	hit_plane(t_plane *pl, t_ray *ray)
{
	double	dot_denom;
	double	t;
	t_vec	dist;

	dot_denom = vec_dot(pl->normal, ray->dir);
	if (fabs(dot_denom) < 1e-6)
		return (-1.0);
	dist = vec_sub(pl->point, ray->origin);
	t = vec_dot(dist, pl->normal) / dot_denom;
	if (t < 0.001)
		return (-1.0);
	return (t);
}
