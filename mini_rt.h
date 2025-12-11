
#ifndef MINI_RT_H
# define MINI_RT_H

#include <stdio.h>
#include "./get_next_line/get_next_line.h"
#include <math.h>


#define HEIGHT 1080
#define WIDTH 1920
#define M_PI 3.14159265358979323846
#define SHARPNESS 100.0


#define OBJ_NONE 0
#define OBJ_SPHERE 1
#define OBJ_PLANE 2
#define OBJ_CYLINDER 3


typedef struct s_collector
{
	void				*value;
	struct s_collector *next;
}	t_collector;

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

typedef struct s_ray
{
    t_vec origin;    // Işının çıktığı yer (Kamera)
    t_vec dir;       // Işının yönü (Piksele doğru)
} t_ray;

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_ambient
{
    float ratio;
    int red;
    int green;
    int blue;
} t_ambient;

typedef struct s_camera
{
    t_vec   origin;     // coord_x, y, z yerine
    t_vec   dir;        // vector_x, y, z yerine (Normalize edilmiş yön)
    int     fov;        // view_degrees

	// --- ÖN HESAPLANAN DEĞERLER (Setup aşamasında dolacak) ---
    t_vec   viewport_u;     // Ekranın yatay vektörü (Sağa doğru ne kadar gidiyor)
    t_vec   viewport_v;     // Ekranın dikey vektörü (Aşağı doğru ne kadar gidiyor)
    t_vec   pixel_delta_u;  // Bir piksel sağa gitmek için gereken minik adım
    t_vec   pixel_delta_v;  // Bir piksel aşağı gitmek için gereken minik adım
    t_vec   upper_left;     // Ekranın sol üst köşesinin uzaydaki koordinatı
} t_camera;

typedef struct s_light
{
    t_vec   center;     // Işığın konumu
    float   brightness;
    int     color;      // RGB birleşik
} t_light;

typedef struct s_sphere
{
    t_vec           center;  // coord_x, coord_y, coord_z yerine
    double          radius;  // diam / 2 (Formüllerde hep yarıçap kullanılır)
    int             color;   // red, green, blue birleşimi (HEX kodu)
    struct s_sphere *next;   // Bağlı liste yapın aynen kalıyor
} t_sphere;

typedef struct s_plane
{
    t_vec           point;   // Düzlemin üzerindeki herhangi bir nokta
    t_vec           normal;  // Düzlemin yüzey normali (yönü)
    int             color;   // RGB birleşik
    struct s_plane  *next;
}   t_plane;

typedef struct  s_cylinder
{
    t_vec               center; // Taban merkezi
    t_vec               axis;   // Silindirin uzandığı eksen (Normal)
    float               diam;   // Çap
    float               height; // Boy
    int                 color;  // RGB birleşik
    struct s_cylinder   *next;
}   t_cylinder;

typedef struct s_mlx
{
	void *mlx;
	void *mlx_win;
	t_img_data img;
}	t_mlx;

typedef struct s_all
{
	t_mlx 		mlx;
    t_ambient	*ambient;
	t_collector	*collector;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_all;


void print_all(t_all *all);


char	**ft_split(char const *s, char c, t_all *all);
void	free_split(char **args);
int		ft_strcmp(char *s1, char *s2);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
char	*collector_dup(char *str, t_all *all);
void	file_check(int ac, char **av);
void    init_data(char **line, t_all *all);
void	clean_collector(t_all *all);
void	print_error(char *error, t_all *all);
void	check_number(int number, char type, t_all *all);
void	init_rgb(int *rgb, char *value, t_all *all);
void    *safe_malloc(int size, t_all *all);
void	*ft_calloc(int nmemb, int size);
float	ft_atof(const char *str, char type, t_all *all);
void	init_cylinder(char **args, t_all *all);
void	init_plane(char **args, t_all *all);
void	init_sphere(char **args, t_all *all);
void    init_coord(t_vec *vec, char *value, t_all *all);
void    init_vector(t_vec *vec, char *value, t_all *all);
int		ft_atoi(char *str, char type, t_all *all);
void    check_float_number(float number, char type, t_all *all);  
void    visualize(t_all *all);
int trace_ray(t_all *all, t_ray *ray);
double hit_sphere(t_sphere *sp, t_ray *ray);
double hit_plane(t_plane *pl, t_ray *ray);
double hit_cylinder(t_cylinder *cy, t_ray *ray);

t_vec   vec_sub(t_vec v1, t_vec v2);
double  vec_dot(t_vec v1, t_vec v2);
t_vec   vec_add(t_vec v1, t_vec v2);
t_vec   vec_mul(t_vec v, double t);
t_vec   vec_norm(t_vec v);
t_vec   vec_cross(t_vec v1, t_vec v2);
int		create_trgb(int t, int r, int g, int b);
void 	setup_camera(t_all *all);
void	init_mlx(t_all *all);

#endif