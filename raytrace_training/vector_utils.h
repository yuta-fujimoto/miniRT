#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include "miniRT.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

void        sub(t_vec3* o, const t_vec3*a, const t_vec3*b);
double      dot(const t_vec3* a, const t_vec3* b);
double      squared_norm(const t_vec3*v);
double      norm(const t_vec3 *v);
double      normalize(t_vec3* v);
void        cross(t_vec3* o, const t_vec3*a, const t_vec3*b);
const char* vector_str(const t_vec3*v);

#endif /* VECTOR_UTILS_H */
