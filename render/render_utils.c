/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:30:35 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:46:14 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

int	clamp(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}

int	calculate_pixel_color(int obj_color, double intensity)
{
	int	r;
	int	g;
	int	b;

	r = (obj_color >> 16) & 0xFF;
	g = (obj_color >> 8) & 0xFF;
	b = obj_color & 0xFF;
	r = clamp((int)(r * intensity));
	g = clamp((int)(g * intensity));
	b = clamp((int)(b * intensity));
	return (create_trgb(0, r, g, b));
}

int	check_obstacle(double t, double light_dist)
{
	if (t > 0.001 && t < light_dist)
		return (1);
	return (0);
}
