#include "miniRT.h"

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

t_vec3 mult(const t_vec3 a, const t_vec3 b)
{
	t_vec3 ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return (ret);
}

t_vec3 cross(const t_vec3 a, const t_vec3 b)
{
	t_vec3  ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}


double dot(const t_vec3* a, const t_vec3* b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
