/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:45:56 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:46:06 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"

// --- YARDIMCI FONKSİYONLAR ---

int clamp(int value)
{
    if (value > 255) return (255);
    if (value < 0) return (0);
    return (value);
}

int calculate_pixel_color(int obj_color, double intensity)
{
    int r = (obj_color >> 16) & 0xFF;
    int g = (obj_color >> 8) & 0xFF;
    int b = obj_color & 0xFF;

    r = clamp((int)(r * intensity));
    g = clamp((int)(g * intensity));
    b = clamp((int)(b * intensity));

    return (create_trgb(0, r, g, b));
}

// --- GÖLGE KONTROLÜ ---
// Hit point'ten ışığa bir ışın yollar, arada engel var mı bakar.
int is_in_shadow(t_all *all, t_vec hit_point, t_vec light_dir, double light_dist)
{
    t_ray   shadow_ray;
    double  t;

    shadow_ray.origin = hit_point;
    shadow_ray.dir = light_dir;

    // 1. KÜRELERİ KONTROL ET
    t_sphere *sp = all->sphere;
    while (sp)
    {
        t = hit_sphere(sp, &shadow_ray);
        if (t > 0.001 && t < light_dist)
            return (1); // Gölgedeyiz
        sp = sp->next;
    }

    // 2. DÜZLEMLERİ KONTROL ET
    t_plane *pl = all->plane;
    while (pl)
    {
        t = hit_plane(pl, &shadow_ray);
        if (t > 0.001 && t < light_dist)
            return (1);
        pl = pl->next;
    }

    // 3. SİLİNDİRLERİ KONTROL ET
    t_cylinder *cy = all->cylinder;
    while (cy)
    {
        t = hit_cylinder(cy, &shadow_ray);
        if (t > 0.001 && t < light_dist)
            return (1);
        cy = cy->next;
    }

    return (0); // Engel yok
}

// --- AYDINLATMA HESABI ---
int compute_lighting(t_all *all, t_vec hit_point, t_vec normal, int obj_color, t_vec view_dir)
{
    t_light *light = all->light;
    double  intensity;
    t_vec   light_vec;
    t_vec   light_dir;
    double  light_dist;
    double  dot_diffuse;
    
    // Specular değişkenleri
    t_vec   reflect_dir;
    double  dot_specular;
    double  shininess = SHARPNESS; // Parlaklık şiddeti (Arttıkça nokta küçülür ve keskinleşir)

    // 1. Ambient (Ortam) Işığı
    intensity = all->ambient->ratio;

    // 2. Işık Yönü ve Mesafesi
    light_vec = vec_sub(light->center, hit_point);
    light_dist = sqrt(vec_dot(light_vec, light_vec));
    light_dir = vec_norm(light_vec);

    // 3. Diffuse (Açı) Hesabı (Normal . LightDir)
    dot_diffuse = vec_dot(normal, light_dir);

    if (dot_diffuse > 0)
    {
        // 4. Gölge Kontrolü
        if (is_in_shadow(all, hit_point, light_dir, light_dist))
        {
             // Gölgedeyiz, sadece ambient kalır.
        }
        else
        {
            // Diffuse ekle
            intensity += light->brightness * dot_diffuse;

            // --- 5. SPECULAR (PARLAMA) HESABI --- ✨
            
            // Yansıma Vektörü Formülü: R = 2*(N.L)*N - L
            t_vec v_mul_res = vec_mul(normal, 2.0 * dot_diffuse);
            reflect_dir = vec_sub(v_mul_res, light_dir);
            reflect_dir = vec_norm(reflect_dir); // Normalize et

            // Yansıma ile Bakış açısı arasındaki ilişki (R . V)
            dot_specular = vec_dot(reflect_dir, view_dir);

            if (dot_specular > 0)
            {
                // Parlaklık üssü (pow) ile keskinleştirme
                double specular_intensity = pow(dot_specular, shininess);
                intensity += light->brightness * specular_intensity;
            }
        }
    }
    return (calculate_pixel_color(obj_color, intensity));
}

// --- ANA TRACE FONKSİYONU ---
int trace_ray(t_all *all, t_ray *ray)
{
    double      t;
    double      closest_t = 1.0 / 0.0; // Sonsuz
    int         hit_type = OBJ_NONE;
    void        *hit_obj = NULL;

    // --- OBJELERİ TARA ---
    t_sphere *sp = all->sphere;
    while (sp)
    {
        t = hit_sphere(sp, ray);
        if (t > 0.001 && t < closest_t)
        {
            closest_t = t;
            hit_type = OBJ_SPHERE;
            hit_obj = sp;
        }
        sp = sp->next;
    }

    t_plane *pl = all->plane;
    while (pl)
    {
        t = hit_plane(pl, ray);
        if (t > 0.001 && t < closest_t)
        {
            closest_t = t;
            hit_type = OBJ_PLANE;
            hit_obj = pl;
        }
        pl = pl->next;
    }

    t_cylinder *cy = all->cylinder;
    while (cy)
    {
        t = hit_cylinder(cy, ray);
        if (t > 0.001 && t < closest_t)
        {
            closest_t = t;
            hit_type = OBJ_CYLINDER;
            hit_obj = cy;
        }
        cy = cy->next;
    }

    if (hit_type == OBJ_NONE)
        return (0x000000); // Hiçbir şeye çarpmadı (Siyah)

    // --- NORMAL VE RENK HAZIRLIĞI ---
    t_vec hit_point = vec_add(ray->origin, vec_mul(ray->dir, closest_t));
    t_vec normal = {0, 0, 0};
    int   obj_color = 0;

    if (hit_type == OBJ_SPHERE)
    {
        t_sphere *s = (t_sphere *)hit_obj;
        normal = vec_norm(vec_sub(hit_point, s->center));
        obj_color = s->color;
    }
    else if (hit_type == OBJ_PLANE)
    {
        t_plane *p = (t_plane *)hit_obj;
        normal = p->normal;
        obj_color = p->color;
    }
    else if (hit_type == OBJ_CYLINDER)
    {
        t_cylinder *c = (t_cylinder *)hit_obj;
        t_vec oc = vec_sub(hit_point, c->center);
        double dot = vec_dot(c->axis, oc);
        t_vec axis_comp = vec_mul(c->axis, dot);
        normal = vec_norm(vec_sub(oc, axis_comp));
        obj_color = c->color;
    }

    // Normal düzeltme (Ters yüzey kontrolü)
    if (vec_dot(ray->dir, normal) > 0)
        normal = vec_mul(normal, -1);

    // Shadow Acne için noktayı hafifçe ötele
    hit_point = vec_add(hit_point, vec_mul(normal, 0.0001));

    // --- YENİ: Bakış yönünü hesapla ---
    // Işın kameradan objeye gidiyordu, tersi objeden kameraya bakar.
    t_vec view_dir = vec_mul(ray->dir, -1.0);
    view_dir = vec_norm(view_dir); // Garanti olsun diye normalize

    // Yeni parametre ile çağır
    return (compute_lighting(all, hit_point, normal, obj_color, view_dir));
}