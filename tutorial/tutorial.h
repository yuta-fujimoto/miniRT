#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include "miniRT.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)
#define CALD(a,b,c) (SQR(b) - 4 * a * c)

typedef enum e_discriminant
{
	A,
	B,
	C,
	D,
	DIS_NUM
}	t_dis;

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
	t_vec3	vec_onscrn;
	t_vec3	vec_view;
	t_vec3	vec_light;
	t_vec3	vec_ray;
	t_vec3	vec_ctr;
	t_vec3	vec_ctr_to_view;
	double  radius;
	double	dis[DIS_NUM];
	double	t;
}	t_info;

int         ft_exit(t_data *data);
int         key_hook(int keycode, t_data *data);

t_vec3      vec3(double x, double y, double z);
t_vec3      sub(const t_vec3*a, const t_vec3*b);
double      dot(const t_vec3* a, const t_vec3* b);
double      squared_norm(const t_vec3*v);
double      norm(const t_vec3 *v);
double      normalize(t_vec3* v);
t_vec3      cross(const t_vec3*a, const t_vec3*b);
const char* vector_str(const t_vec3*v);

#endif /* VECTOR_UTILS_H */
