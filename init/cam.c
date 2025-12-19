/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:11:11 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:12:59 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <math.h>

static void	calc_viewport_and_deltas(t_camera *cam, t_vec u, t_vec v)
{
	double	theta;
	double	h;
	double	vp_height;
	double	vp_width;

	theta = (cam->fov * M_PI) / 180.0;
	h = tan(theta / 2.0);
	vp_height = 2.0 * h;
	vp_width = vp_height * ((double)WIDTH / (double)HEIGHT);
	cam->viewport_u = vec_mul(u, vp_width);
	cam->viewport_v = vec_mul(v, -vp_height);
	cam->pixel_delta_u = vec_mul(cam->viewport_u, 1.0 / WIDTH);
	cam->pixel_delta_v = vec_mul(cam->viewport_v, 1.0 / HEIGHT);
}

static void	calc_upper_left(t_camera *cam, t_vec w)
{
	t_vec	vp_center;
	t_vec	half_u;
	t_vec	half_v;
	t_vec	half_pixel;

	vp_center = vec_sub(cam->origin, w);
	half_u = vec_mul(cam->viewport_u, 0.5);
	half_v = vec_mul(cam->viewport_v, 0.5);
	cam->upper_left = vec_sub(vp_center, half_u);
	cam->upper_left = vec_sub(cam->upper_left, half_v);
	half_pixel = vec_add(vec_mul(cam->pixel_delta_u, 0.5),
			vec_mul(cam->pixel_delta_v, 0.5));
	cam->upper_left = vec_add(cam->upper_left, half_pixel);
}

void	setup_camera(t_all *all)
{
	t_camera	*cam;
	t_vec		w;
	t_vec		u;
	t_vec		v;
	t_vec		up_guide;

	cam = all->camera;
	w = vec_norm(vec_mul(cam->dir, -1));
	up_guide = (t_vec){0, 1, 0};
	if (fabs(w.y) > 0.999)
		up_guide = (t_vec){0, 0, 1};
	u = vec_norm(vec_cross(up_guide, w));
	v = vec_cross(w, u);
	calc_viewport_and_deltas(cam, u, v);
	calc_upper_left(cam, w);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
