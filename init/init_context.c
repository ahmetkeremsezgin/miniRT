/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:46:36 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/10 11:46:36 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_rt.h"
#include <stdlib.h>

// Bu fonksiyonu parser bittikten sonra, render başlamadan ÖNCE bir kere çağıracağız.
void setup_camera(t_all *all)
{
    t_camera *cam = all->camera;
    // 1. FOV'dan viewport boyutlarını hesapla
    double theta = (cam->fov * M_PI) / 180.0;
    double h = tan(theta / 2.0);
    double viewport_height = 2.0 * h;
    double viewport_width = viewport_height * ((double)WIDTH / (double)HEIGHT);
    
    // 2. Kamera koordinat sistemini oluştur
    t_vec w = vec_norm(vec_mul(cam->dir, -1));
    t_vec up_guide = {0, 1, 0};
    if (fabs(w.y) > 0.999) 
        up_guide = (t_vec){0, 0, 1};
    t_vec u = vec_norm(vec_cross(up_guide, w));
    t_vec v = vec_cross(w, u);

    // 3. Viewport Vektörlerini Oluştur
    cam->viewport_u = vec_mul(u, viewport_width);
    cam->viewport_v = vec_mul(v, -viewport_height);
    // 4. Delta hesaplama
    cam->pixel_delta_u = vec_mul(cam->viewport_u, 1.0 / WIDTH);
    cam->pixel_delta_v = vec_mul(cam->viewport_v, 1.0 / HEIGHT);

    // 5. Sol Üst Köşeyi (Upper Left) Bul    
    t_vec viewport_center = vec_sub(cam->origin, w);
    t_vec half_u = vec_mul(cam->viewport_u, 0.5);
    t_vec half_v = vec_mul(cam->viewport_v, 0.5);
    
    cam->upper_left = vec_sub(viewport_center, half_u);
    cam->upper_left = vec_sub(cam->upper_left, half_v);
    
    t_vec half_pixel = vec_add(vec_mul(cam->pixel_delta_u, 0.5), vec_mul(cam->pixel_delta_v, 0.5));
    cam->upper_left = vec_add(cam->upper_left, half_pixel);
    
    printf("Camera setup completed.\n");
}

void	init_rgb(int *rgb, char *value, t_all *all)
{
	char	**args;
	args = ft_split(value, ',', all);
	if(!args || args[3] != NULL)
		print_error("invalid argument size", all);
	rgb[0] = ft_atoi(args[0], 'c', all);
	rgb[1] = ft_atoi(args[1], 'c', all);
	rgb[2] = ft_atoi(args[2], 'c' , all);
	//free_split(args);
}

void	init_ambient(char **args, t_all *all)
{
	int rgb[3];
	if(all->ambient != NULL)
		print_error("too many ambient size", all);
	if(args[3] != NULL)
		print_error("invalid argument size", all);
	all->ambient = (t_ambient *)safe_malloc(sizeof(t_ambient), all);
	all->ambient->ratio = ft_atof(args[1], 'r', all);
	init_rgb(rgb, args[2], all);
	all->ambient->red = rgb[0];
	all->ambient->green = rgb[1];
	all->ambient->blue = rgb[2];
}
void    init_camera(char **args, t_all *all)
{
    // float coord[3] ve float vector[3] dizilerine artık gerek yok!
    
    if(all->camera != NULL)
        print_error("too many camera definition", all);
    if(args[4] != NULL)
        print_error("invalid camera argument size", all);
        
    all->camera = (t_camera *)safe_malloc(sizeof(t_camera), all);
    
    // 1. Koordinatları (Origin) doğrudan struct içine yazıyoruz
    init_coord(&all->camera->origin, args[1], all);
    
    // 2. Yön vektörünü (Direction) doğrudan struct içine yazıyoruz
    init_vector(&all->camera->dir, args[2], all);
    
    // 3. FOV (Görüş açısı)
    all->camera->fov = ft_atoi(args[3], 'd', all);
    
    // NOT: İleride render alırken 'dir' vektörünün normalize edilmiş olması gerekecek.
    // Şimdilik ham haliyle bırakıyoruz.
}

void    init_light(char **args, t_all *all)
{
    int rgb[3]; // RGB'yi önce parçalı alıp sonra birleştirmek için bu lazım
    
    if(all->light != NULL)
        print_error("too many light definition", all);
    if(args[4] != NULL)
        print_error("invalid light argument size", all);
        
    all->light = (t_light *)safe_malloc(sizeof(t_light), all);
    
    // 1. Işığın konumu (Center)
    init_coord(&all->light->center, args[1], all);
    
    // 2. Parlaklık oranı
    all->light->brightness = ft_atof(args[2], 'b', all);
    
    // 3. Işık rengi (Bonus kısmı için renkli ışık gerekebilir, zorunlu değilse beyaz kalır)
    init_rgb(rgb, args[3], all);
    all->light->color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
}

void    init_data(char **line, t_all *all)
{
    if(ft_strcmp(line[0], "A") == 0)
		init_ambient(line, all);
    else if(ft_strcmp(line[0], "C") == 0)
        init_camera(line, all);
    else if(ft_strcmp(line[0], "L") == 0)
        init_light(line, all);
    else if(ft_strcmp(line[0], "sp") == 0)
        init_sphere(line, all);
    else if(ft_strcmp(line[0], "pl") == 0)
    	init_plane(line, all);
    else if(ft_strcmp(line[0], "cy") == 0)
        init_cylinder(line, all);
    else
		print_error("invalid element name", all);
}
