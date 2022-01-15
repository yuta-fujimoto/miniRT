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

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

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
} t_light;

typedef struct s_sphere {
	t_vec3 center;
	double diameter;
	t_color c;
} t_sphere;

typedef struct s_plane {
	t_vec3 pos;
	t_vec3 norm_ori_vec;
	t_color c;
} t_plane;

typedef struct s_cylinder {
	t_vec3 pos;
	t_vec3 norm_ori_vec;
	double diameter;
	double height;
	t_color c;
} t_cylinder;

typedef struct s_world {
	t_list *obj_list;
	t_amb_light amb_light;
	t_camera camera;
	t_light light;
	bool	env_elems_exists[3];
} t_world;

bool atovec3(char const *nptr, t_vec3 *rlt);
bool atocol(char const *nptr, t_color *rlt);
bool is_normalized_vector(t_vec3 v);
// vector, color

t_world *parser(char *fn);
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
t_world	*end_world(t_world *w);
void	safe_free(void *p);
// utils

#endif
