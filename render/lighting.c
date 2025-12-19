/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:32:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:48:32 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <math.h>

int	combine_light_obj(int obj_color, int amb_rgb, double diff)
{
	int	rgb[3];
	int	amb[3];

	rgb[0] = (obj_color >> 16) & 0xFF;
	rgb[1] = (obj_color >> 8) & 0xFF;
	rgb[2] = obj_color & 0xFF;
	amb[0] = (amb_rgb >> 16) & 0xFF;
	amb[1] = (amb_rgb >> 8) & 0xFF;
	amb[2] = amb_rgb & 0xFF;
	rgb[0] = clamp((int)(rgb[0] * ((double)amb[0] / 255.0 + diff)));
	rgb[1] = clamp((int)(rgb[1] * ((double)amb[1] / 255.0 + diff)));
	rgb[2] = clamp((int)(rgb[2] * ((double)amb[2] / 255.0 + diff)));
	return (create_trgb(0, rgb[0], rgb[1], rgb[2]));
}

int	compute_lighting(t_all *all, t_vec hit, t_vec normal, int obj_color)
{
	t_vec	l_dir;
	double	l_dist;
	double	dot;
	double	diff;
	int		amb;

	amb = calculate_pixel_color(all->ambient->color, all->ambient->ratio);
	l_dir = vec_sub(all->light->center, hit);
	l_dist = sqrt(vec_dot(l_dir, l_dir));
	l_dir = vec_norm(l_dir);
	dot = vec_dot(normal, l_dir);
	diff = 0;
	if (dot > 0 && !is_in_shadow(all, hit, l_dir, l_dist))
		diff = all->light->brightness * dot;
	return (combine_light_obj(obj_color, amb, diff));
}
