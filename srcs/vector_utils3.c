#include "miniRT.h"

double	dot(const t_vec3 *a, const t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	squared_norm(const t_vec3 *v)
{
	return (sqr(v->x) + sqr(v->y) + sqr(v->z));
}

double	norm(const t_vec3 *v)
{
	return (sqrt(squared_norm(v)));
}

double	normalize(t_vec3 *v)
{
	double	vnorm;

	vnorm = norm(v);
	if (vnorm == 0)
	{
		*v = vec3(0, 0, 0);
		return (0);
	}
	v->x /= vnorm;
	v->y /= vnorm;
	v->z /= vnorm;
	return (vnorm);
}
