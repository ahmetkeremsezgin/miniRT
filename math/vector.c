/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:00:24 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:00:27 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

// Vektör Toplama
t_vec vec_add(t_vec v1, t_vec v2)
{
    t_vec res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return (res);
}

// Vektör Çıkarma
t_vec vec_sub(t_vec v1, t_vec v2)
{
    t_vec res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return (res);
}
double vec_dot(t_vec v1, t_vec v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// Vektör ile Sayı Çarpma (Uzatma/Kısaltma)
t_vec vec_mul(t_vec v, double t)
{
    t_vec res;
    res.x = v.x * t;
    res.y = v.y * t;
    res.z = v.z * t;
    return (res);
}

// Vektör Normalizasyonu (Boyunu 1 yapma)
t_vec vec_norm(t_vec v)
{
    double len;
    
    len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    if (len == 0)
        return (v);
    v.x /= len;
    v.y /= len;
    v.z /= len;
    return (v);
}

// Çapraz Çarpım (Cross Product) - İki vektöre de dik olan 3. vektörü bulur
// Kameranın "Sağını" bulmak için bunu kullanacağız.
t_vec vec_cross(t_vec v1, t_vec v2)
{
    t_vec res;
    
    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return (res);
}