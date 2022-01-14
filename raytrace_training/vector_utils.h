#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <stdio.h>
#include <math.h>
#include <string.h>

#define SQR(x) ((x)*(x))
#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)
#define CLAMP(v,minv,maxv) MIN(MAX(v,minv),maxv)

typedef struct {
  double x,y,z;
} vector_t;

void        sub(vector_t* o, const vector_t*a, const vector_t*b);
double      dot(const vector_t* a, const vector_t* b);
double      squared_norm(const vector_t*v);
double      norm(const vector_t *v);
double      normalize(vector_t* v);
void        cross(vector_t* o, const vector_t*a, const vector_t*b);
const char* vector_str(const vector_t*v);

#endif /* VECTOR_UTILS_H */
