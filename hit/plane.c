/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:15:25 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:25:00 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

double hit_plane(t_plane *pl, t_ray *ray)
{
    // Payda hesabı: Normal ile Işın Yönü'nün nokta çarpımı
    double dot_denom = vec_dot(pl->normal, ray->dir);
    
    // Eğer sonuç 0'a çok yakınsa, ışın düzleme paraleldir.
    // Çarpışma olmaz veya düzlemin içinden sonsuza gider.
    if (fabs(dot_denom) < 1e-6)
        return (-1.0);
        
    t_vec dist = vec_sub(pl->point, ray->origin);
    double t = vec_dot(dist, pl->normal) / dot_denom;
    
    // t < 0 ise düzlem kameranın arkasındadır.
    if (t < 0.001) // 0.001 shadow acne için güvenlik payı
        return (-1.0);
        
    return (t);
}