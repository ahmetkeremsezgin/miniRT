/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asezgin <asezgin@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:56:44 by asezgin           #+#    #+#             */
/*   Updated: 2025/12/17 13:56:44 by asezgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINI_RT_H
# define MINI_RT_H

# include "./get_next_line/get_next_line.h"

# define HEIGHT 1080
# define WIDTH 1920
# define SHARPNESS 100.0

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define OBJ_NONE 0
# define OBJ_SPHERE 1
# define OBJ_PLANE 2
# define OBJ_CYLINDER 3

typedef struct s_collector
{
	void				*value;
	struct s_collector	*next;
}	t_collector;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_hit
{
	double	t;
	int		type;
	void	*obj;
}	t_hit;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_ambient
{
	float	ratio;
	int		color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	origin;
	t_vec	dir;
	int		fov;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	pixel_delta_u;
	t_vec	pixel_delta_v;
	t_vec	cam_view_dir;
	t_vec	upper_left;
}	t_camera;

typedef struct s_light
{
	t_vec	center;
	float	brightness;
	int		color;
}	t_light;

typedef struct s_sphere
{
	t_vec			center;
	double			radius;
	int				color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vec			point;
	t_vec			normal;
	int				color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vec				center;
	t_vec				axis;
	float				diam;
	float				height;
	int					color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img_data	img;
}	t_mlx;

typedef struct s_all
{
	t_mlx		mlx;
	t_ambient	*ambient;
	t_collector	*collector;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_vec		cam_view_dir;
}	t_all;

char	**ft_split(char const *s, char c, t_all *all);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
char	*collector_dup(char *str, t_all *all);
void	file_check(int ac, char **av);
void	init_data(char **line, t_all *all);
void	clean_collector(t_all *all);
void	print_error(char *error, t_all *all);
void	check_number(int number, char type, t_all *all);
void	init_rgb(int *rgb, char *value, t_all *all);
void	*safe_malloc(int size, t_all *all);
void	*ft_calloc(int nmemb, int size);
float	ft_atof(const char *str, char type, t_all *all);
void	init_cylinder(char **args, t_all *all);
void	init_plane(char **args, t_all *all);
void	init_sphere(char **args, t_all *all);
void	init_coord(t_vec *vec, char *value, t_all *all);
void	init_vector(t_vec *vec, char *value, t_all *all);
int		ft_atoi(char *str, char type, t_all *all);
void	check_float_number(float number, char type, t_all *all);
void	init_mlx(t_all *all);
void	check_obj(t_all *all);

t_vec	vec_sub(t_vec v1, t_vec v2);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v, double t);
t_vec	vec_norm(t_vec v);
t_vec	vec_cross(t_vec v1, t_vec v2);

void	setup_camera(t_all *all);
int		trace_ray(t_all *all, t_ray *ray);
double	hit_sphere(t_sphere *sp, t_ray *ray);
double	hit_plane(t_plane *pl, t_ray *ray);
double	hit_cylinder(t_cylinder *cy, t_ray *ray);
void	get_closest_obj(t_all *all, t_ray *ray, t_hit *rec);

int		clamp(int value);
int		create_trgb(int t, int r, int g, int b);
int		check_obstacle(double t, double light_dist);
int		is_in_shadow(t_all *all, t_vec hit_p, t_vec l_dir, double dist);
int		calculate_pixel_color(int obj_color, double intensity);
int		compute_lighting(t_all *all, t_vec hit, t_vec normal, int color);

#endif