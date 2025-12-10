/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:01:57 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 10:11:43 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

double hit_sphere(t_sphere *sp, t_ray *ray)
{
    t_vec   oc;
    double  a, b, c;
    double  discriminant;
    double  t1, t2;

    oc = vec_sub(ray->origin, sp->center);
    a = vec_dot(ray->dir, ray->dir);
    b = 2.0 * vec_dot(oc, ray->dir);
    c = vec_dot(oc, oc) - (sp->radius * sp->radius);
    discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return (-1.0); // Kesişim yok

    // Kökleri buluyoruz: (-b ± sqrt(delta)) / 2a
    t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    // En küçük POZİTİF t değerini istiyoruz (Kameranın önündeki en yakın nokta)
    if (t1 > 0.0)
        return (t1);
    if (t2 > 0.0)
        return (t2);
    
    return (-1.0); // Küre arkamızda kaldıysa
}
