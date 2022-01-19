#include "miniRT.h"

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
  double vnorm;

  vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}
