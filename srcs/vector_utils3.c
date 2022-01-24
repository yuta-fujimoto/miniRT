#include "miniRT.h"

double	dot(const t_vec3 *a, const t_vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	squared_norm(const t_vec3 *v)
{
	return (SQR(v->x) + SQR(v->y) + SQR(v->z));
}

double	norm(const t_vec3 *v)
{
	return (sqrt(squared_norm(v)));
}

double	normalize(t_vec3 *v)
{
	double	vnorm;

	vnorm = norm(v);
	v->x /= vnorm;
	v->y /= vnorm;
	v->z /= vnorm;
	return (vnorm);
}
