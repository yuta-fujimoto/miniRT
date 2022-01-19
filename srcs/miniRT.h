#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include "keysymdef.h"
#include "../gnl/get_next_line_bonus.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

#define W_IMG 500
#define H_IMG 500
#define REF_FACTOR_MIRROR 0.3
#define ILLUMI_RATE_ENV 0.1
#define ILLUMI_RATE_DIR 1.0
#define GLOSSINESS 8

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

enum Object
{
	Sphere,
	Plane,
	Cylinder
};

typedef struct s_vec3
{
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_ray
{
	t_vec3 start;
	t_vec3 direction;
} t_ray;

typedef struct s_color
{
	double r;
	double g;
	double b;
} t_color;

typedef struct s_intersection_point
{
	double distance;
	t_vec3 pos;
	t_vec3 normal;
} t_intersection_point;

typedef struct s_material
{
	t_color	ambient_ref;
	t_color	diffuse_ref;
	t_color	specular_ref;
	double	shininess;
}	t_material;

typedef struct s_amb_light {
	double ratio;
	t_color c;
} t_amb_light;

typedef struct s_camera {
	t_vec3 pos;
	t_vec3 norm_ori_vec;
	int fov;
} t_camera;

typedef struct s_light
{
	double ratio;
	t_vec3 pos;
}	t_light;

typedef struct s_sphere {
	t_vec3 center;
	double diameter;
	t_color c;
}	t_sphere;

typedef struct s_plane {
	t_vec3 pos;
	t_vec3 norm_ori_vec;
	t_color c;
}	t_plane;

typedef struct s_cylinder {
	t_vec3 pos;
	t_vec3 norm_ori_vec;
	double diameter;
	double height;
	t_color c;
}	t_cylinder;

typedef struct s_world {
	t_list		*obj_list;
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
	bool		env_elems_exists[3];
} t_world;

bool	atocol(char const *nptr, t_color *rlt);
t_color	color(double r, double g, double b);
t_color	cmult(const t_color a, const t_color b);
// color

bool		atovec3(char const *nptr, t_vec3 *rlt);
bool		is_normalized_vector(t_vec3 v);
t_vec3      vec3(double x, double y, double z);
t_vec3 add(const t_vec3 a, const t_vec3 b);
t_vec3      sub(const t_vec3 a, const t_vec3 b);
t_vec3 		mult(const t_vec3 a, const t_vec3 b);
t_vec3		times(const double nb, const t_vec3 a);
double      dot(const t_vec3 *a, const t_vec3 *b);
double      squared_norm(const t_vec3 *v);
double      norm(const t_vec3 *v);
double      normalize(t_vec3* v);
t_vec3      cross(const t_vec3 a, const t_vec3 b);
// vector

bool parser(char *fn, t_world *w);
bool parser_amb_light(t_world *world, char **info);
bool parser_light(t_world *world, char **info);
bool parser_camera(t_world *world, char **info);
bool parser_sphere(t_world *world, char **info);
bool parser_plane(t_world *world, char **info);
bool parser_cylinder(t_world *world, char **info);
// parser

void print_world(t_world *w);
void print_color(t_color c, char *prefix);
void print_vec3(t_vec3 v, char *prefix);
// print_debug

void	ft_str_arr_free(char **str_arr);
int		ft_str_arr_len(char **str_arr);
bool	end_world(t_world *w, bool rlt);
void	safe_free(void *p);
// utils

bool	raytrace(const t_world *w, const t_ray *eye_ray, t_color *out_col);
bool	intersection_test(const t_list *obj, const t_ray *ray, t_intersection_point *out_intp);
// raytrace

int		key_hook(int keycode, t_data *data);
int 	ft_exit(t_data *data);
// hooks

#endif
