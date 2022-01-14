#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include "miniRT.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_vectors {
  t_vec3	vec_onscrn;
	t_vec3	vec_view;
	t_vec3	vec_ray;
	t_vec3	vec_ctr;
	t_vec3	vec_ctr_to_view;
  double  radius;
}	t_vecs;

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

t_vec3      vec3(double x, double y, double z);
void        sub(t_vec3* o, const t_vec3*a, const t_vec3*b);
double      dot(const t_vec3* a, const t_vec3* b);
double      squared_norm(const t_vec3*v);
double      norm(const t_vec3 *v);
double      normalize(t_vec3* v);
void        cross(t_vec3* o, const t_vec3*a, const t_vec3*b);
const char* vector_str(const t_vec3*v);

#endif /* VECTOR_UTILS_H */
