/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:15:03 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:25:17 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

// Çarpışma noktasının silindirin boy sınırları içinde olup olmadığını kontrol eder.
// Merkez noktasını silindirin TAM ORTASI kabul ediyoruz.
// Bu yüzden -height/2 ile +height/2 arasını kontrol ediyoruz.
static int check_height(t_cylinder *cy, t_ray *ray, double t)
{
    t_vec   hit_point;
    double  hit_height;

    // P = O + t*D
    hit_point = vec_add(ray->origin, vec_mul(ray->dir, t));
    
    // Silindir ekseni üzerindeki izdüşümünü buluyoruz.
    // (P - C) . Axis
    t_vec oc = vec_sub(hit_point, cy->center);
    hit_height = vec_dot(oc, cy->axis);

    // Eğer yükseklik, boyun yarısından fazlaysa (yukarıda veya aşağıda) geçersizdir.
    if (fabs(hit_height) > (cy->height / 2.0))
        return (0); // Geçersiz
    return (1); // Geçerli
}

double hit_cylinder(t_cylinder *cy, t_ray *ray)
{
    t_vec   oc;
    double  a, b, c, discriminant;
    double  t1, t2;

    oc = vec_sub(ray->origin, cy->center);

    // Quadratic formül katsayıları (Silindir için özelleştirilmiş)
    // Dot(D, D) - Dot(D, A)^2
    double dot_dir_axis = vec_dot(ray->dir, cy->axis);
    double dot_oc_axis = vec_dot(oc, cy->axis);

    a = vec_dot(ray->dir, ray->dir) - (dot_dir_axis * dot_dir_axis);
    b = 2 * (vec_dot(ray->dir, oc) - (dot_dir_axis * dot_oc_axis));
    c = vec_dot(oc, oc) - (dot_oc_axis * dot_oc_axis) - ((cy->diam / 2) * (cy->diam / 2));

    discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (-1.0);

    // İki kökü de buluyoruz (Giriş ve Çıkış noktaları)
    double sqrt_disc = sqrt(discriminant);
    t1 = (-b - sqrt_disc) / (2 * a);
    t2 = (-b + sqrt_disc) / (2 * a);

    // 1. En yakın noktayı (t1) kontrol et
    // Eğer t1 pozitifse VE boy sınırları içindeyse, onu döndür.
    if (t1 > 0.001 && check_height(cy, ray, t1))
        return (t1);

    // 2. Eğer t1 geçersizse (arkada kaldıysa veya boyu aştıysa), t2'yi kontrol et
    // Bu sayede silindirin içini veya arkadaki duvarını görebiliriz.
    if (t2 > 0.001 && check_height(cy, ray, t2))
        return (t2);

    return (-1.0);
}