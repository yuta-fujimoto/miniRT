#include "tutorial.h"

t_vec3 vec3(const double x, const double y, const double z)
{
  t_vec3  ret;

  ret.x = x;
  ret.y = y;
  ret.z = z;
  return (ret);
}

t_vec3 add(const t_vec3 a, const t_vec3 b)
{
  t_vec3 ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
  return (ret);
}

t_vec3 sub(const t_vec3 a, const t_vec3 b)
{
  t_vec3 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
  return (ret);
}

t_vec3 times(const double nb, const t_vec3 a)
{
  t_vec3 ret;
	ret.x = nb * a.x;
	ret.y = nb * a.y;
	ret.z = nb * a.z;
  return (ret);
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
  double vnorm;

  vnorm = norm(v);
  v->x /= vnorm;
  v->y /= vnorm;
  v->z /= vnorm;
  return vnorm;
}

t_vec3 cross(const t_vec3 a, const t_vec3 b)
{
  t_vec3  ret;
  ret.x = a.y * b.z - a.z * b.y;
  ret.y = a.z * b.x - a.x * b.z;
  ret.z = a.x * b.y - a.y * b.x;
  return (ret);
}
