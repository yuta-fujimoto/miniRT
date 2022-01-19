#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include "miniRT.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF
#define NAVY 0x00000080
#define PURPLE 0x00800080

#define W_IMG 512
#define H_IMG 512
#define REF_FACTOR_ENV 0.01
#define REF_FACTOR_DIFFUSE 0.69
#define REF_FACTOR_MIRROR 0.3
#define ILLUMI_RATE_ENV 0.1
#define ILLUMI_RATE_DIR 1.0
#define GLOSSINESS 8

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef int color_int;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_info {
	t_vec3	pos_onscrn;
	t_vec3	pos_camera;
	t_vec3	pos_light;
	t_vec3	dir_ray;
	t_vec3	vec_ctr;
	t_vec3	vec_ctr_to_view;
	t_vec3	vec_int;
	t_vec3	vec_inc;
	t_vec3	vec_norm;
	double  radius;
	double	buf;
}	t_info;

//hook_funcs.c
int         ft_exit(t_data *data);
int         key_hook(int keycode, t_data *data);

//vector_utils.c
t_vec3      vec3(double x, double y, double z);
t_vec3		add(const t_vec3*a, const t_vec3*b);
t_vec3		add_deep(const t_vec3 a, const t_vec3 b);
t_vec3      sub(const t_vec3*a, const t_vec3*b);
t_vec3		sub_deep(const t_vec3 a, const t_vec3 b);
t_vec3		times(double nb, const t_vec3*a);
double      dot(const t_vec3* a, const t_vec3* b);
double      squared_norm(const t_vec3*v);
double      norm(const t_vec3 *v);
double      normalize(t_vec3* v);
t_vec3      cross(const t_vec3*a, const t_vec3*b);
const char* vector_str(const t_vec3*v);

#endif /* VECTOR_UTILS_H */
