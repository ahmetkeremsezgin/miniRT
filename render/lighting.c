/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:32:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/18 14:35:50 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

static double	calc_specular(t_vec normal, t_vec l_dir, t_vec view, double dot)
{
	t_vec	reflect_dir;
	t_vec	v_mul;
	double	spec_dot;
	double	shininess;

	shininess = SHARPNESS;
	v_mul = vec_mul(normal, 2.0 * dot);
	reflect_dir = vec_sub(v_mul, l_dir);
	reflect_dir = vec_norm(reflect_dir);
	spec_dot = vec_dot(reflect_dir, view);
	if (spec_dot > 0)
		return (pow(spec_dot, shininess));
	return (0.0);
}

int	compute_lighting(t_all *all, t_vec hit, t_vec normal, int color)
{
	t_vec	l_dir;
	double	l_dist;
	double	intensity;
	double	dot;

	intensity = all->ambient->ratio;
	l_dist = sqrt(vec_dot(vec_sub(all->light->center, hit),
				vec_sub(all->light->center, hit)));
	l_dir = vec_norm(vec_sub(all->light->center, hit));
	dot = vec_dot(normal, l_dir);
	if (dot > 0)
	{
		if (!is_in_shadow(all, hit, l_dir, l_dist))
		{
			intensity += all->light->brightness * dot;
			intensity += all->light->brightness * calc_specular(normal,
					l_dir, all->camera->cam_view_dir, dot);
		}
	}
	return (calculate_pixel_color(color, intensity));
}
