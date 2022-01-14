#include "vector_utils.h"

t_vec3 vec3(double x, double y, double z)
{
  t_vec3  ret;

  ret.x = x;
  ret.y = y;
  ret.z = z;
  return (ret);
}

void sub(t_vec3* o, const t_vec3*a, const t_vec3*b)
{
	o->x = a->x - b->x;
	o->y = a->y - b->y;
	o->z = a->z - b->z;
}

double dot(const t_vec3* a, const t_vec3* b)
{
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

double squared_norm(const t_vec3*v)
{
  return SQR(v->x) + SQR(v->y) + SQR(v->z);
}

double norm(const t_vec3 *v)
{
  return sqrt(squared_norm(v));
}

double normalize(t_vec3* v)
{
  double vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

void cross(t_vec3* o, const t_vec3*a, const t_vec3*b)
{
  o->x = a->y * b->z - a->z * b->y;
  o->y = a->z * b->x - a->x * b->z;
  o->z = a->x * b->y - a->y * b->x;
}

const char* vector_str(const t_vec3*v)
{
  static char buf[1024];
  memset(buf, 0, sizeof(buf));
  sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
  return buf;
}
