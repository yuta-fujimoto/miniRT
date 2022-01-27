#ifndef MINIRT_H
# define MINIRT_H

# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include "keysymdef.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

// Assumptions
# define W_IMG 612.0
# define H_IMG 512.0
# define W_SCRN 500.0
# define COEF_SPECULAR_REF 0.3
# define SHININESS 8
# define EPSILON 0.01
# ifndef M_PI
#  define M_PI 3.141592653589793
# endif

typedef enum e_formula
{
	A,
	B,
	C,
	D,
	T1,
	T2,
	FORMULA_NUM
}	t_formula;

typedef enum e_error_status
{
	SUCCESS,
	NOARG,
	EFORMAT,
	SYSERROR,
	NOENV,
	EPARSE,
}	t_error_status;

enum e_Object
{
	Sphere,
	Plane,
	Cylinder
};

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	start;
	t_vec3	direction;
}	t_ray;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_intersection_point
{
	double	distance;
	t_vec3	pos;
	t_vec3	normal;
}	t_intersection_point;

typedef struct s_material
{
	t_color	ambient_ref;
	t_color	diffuse_ref;
	t_color	specular_ref;
	double	shininess;
}	t_material;

typedef struct s_amb_light {
	double	ratio;
	t_color	c;
}	t_amb_light;

typedef struct s_camera {
	t_vec3	pos;
	t_vec3	norm_ori_vec;
	int		fov;
}	t_camera;

typedef struct s_light
{
	double	ratio;
	t_vec3	pos;
}	t_light;

typedef struct s_sphere {
	t_vec3	center;
	double	diameter;
	t_color	c;
}	t_sphere;

typedef struct s_plane {
	t_vec3	pos;
	t_vec3	norm_ori_vec;
	t_color	c;
}	t_plane;

typedef struct s_cylinder {
	t_vec3	pos;
	t_vec3	norm_ori_vec;
	double	diameter;
	double	height;
	t_color	c;
}	t_cylinder;

// default values used in the to3axis()
typedef struct s_default
{
	t_camera	cam;
	t_vec3		vec_ey;
	t_vec3		vec_dx;
	t_vec3		vec_dy;
	double		coef_n;
	double		max_xi;
	double		max_yi;
	double		h_scrn;
	double		half_ws;
	double		half_hs;
}	t_default;

// data used in the add_color()
typedef struct s_refdata {
	t_vec3	ray;
	t_vec3	normal;
	t_vec3	incidence;
	t_vec3	reverseray;
	t_vec3	reflection;
	t_color	norm_dot_inc;
	t_color	light_ratio;
}	t_refdata;

typedef struct s_world {
	t_list		*obj_list;
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
	bool		env_elems_exists[3];
}	t_world;

typedef struct s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_world		w;
}	t_data;

bool	atocol(char const *nptr, t_color *rlt);
t_color	color(double r, double g, double b);
t_color	cmult(const t_color a, const t_color b);
t_color	cadd(const t_color a, const t_color b);
void	cfilter(t_color *a, const double min, const double max);
void	add_color(const t_material *mat, t_refdata *refdata, t_color *out_col);
// color

bool	atovec3(char const *nptr, t_vec3 *rlt);
bool	is_normed_vec(t_vec3 v);
t_vec3	vec3(double x, double y, double z);
t_vec3	add(const t_vec3 a, const t_vec3 b);
t_vec3	sub(const t_vec3 a, const t_vec3 b);
t_vec3	mult(const t_vec3 a, const t_vec3 b);
t_vec3	times(const double nb, const t_vec3 a);
double	dot(const t_vec3 *a, const t_vec3 *b);
double	squared_norm(const t_vec3 *v);
double	norm(const t_vec3 *v);
double	normalize(t_vec3 *v);
t_vec3	cross(const t_vec3 a, const t_vec3 b);
// vector

bool	parser(char *fn, t_world *w);
bool	parser_amb_light(t_world *world, char **info);
bool	parser_light(t_world *world, char **info);
bool	parser_camera(t_world *world, char **info);
bool	parser_sphere(t_world *world, char **info);
bool	parser_plane(t_world *world, char **info);
bool	parser_cylinder(t_world *world, char **info);
// parser

char	*vector_str(const t_vec3 v);
void	print_world(t_world *w);
void	print_color(t_color c, char *prefix);
void	print_vec3(t_vec3 v, char *prefix);
// print_debug

void	ft_str_arr_free(char **str_arr);
int		ft_str_arr_len(char **str_arr);
void	safe_free(void *p);
t_ray	ray(t_vec3 start, t_vec3 direction);
// utils1

double	sqr(double x);
double	min(double a, double b);
double	max(double a, double b);
double	clamp(double x, double min, double max);
double	radians(double	degrees);
// utils2

t_vec3	get_position(const double t, const t_ray *ray);
double	get_t(double form[FORMULA_NUM]);
int		cylinder_height_test(const t_cylinder *cylinder, const t_ray *ray, \
					const double form[FORMULA_NUM], double *out_height);
// intersection_test

bool	raytrace(const t_world *w, const t_ray *eye_ray, t_color *out_col);
bool	intersection_test(const t_list *obj, \
					const t_ray *ray, t_intersection_point *out_intp);
// raytrace

int		key_hook(int keycode, t_data *data);
int		ft_exit(t_data *data, int status);
int		close_window(t_data *data);
// hooks

bool	print_error(const int line_count, const t_error_status error_status);
// error

void	data_init(t_data *data);
//init

#endif
