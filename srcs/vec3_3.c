#include "miniRT.h"

t_vec3 add(const t_vec3 a, const t_vec3 b)
{
  t_vec3 ret;

  ret.x = a.x + b.x;
  ret.y = a.y + b.y;
  ret.z = a.z + b.z;
  return (ret);
}

t_vec3 mul(const t_vec3 a, const t_vec3 b)
{
  t_vec3 ret;
  ret.x = a.x * b.x;
  ret.y = a.y * b.y;
  ret.z = a.z * b.z;

  return (ret);
}

t_vec3 vec3sigma(double i, const t_vec3 a, double j, const t_vec3 b)
{
	return (add(mul(vec3(i, i, i), a), mul(vec3(j, j, j), b)));
}
