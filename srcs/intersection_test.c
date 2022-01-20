#include "miniRT.h"

typedef enum e_formula
{
	A,
	B,
	C,
	D,
	FORMULA_NUM
}	t_formula;

double	get_t(double form[FORMULA_NUM])
{
	double	d_sqrt;
	double	t1;
	double	t2;

	form[D] = SQR(form[B]) - (4 * form[A] * form[C]);
	if (form[D] >= 0)
	{
		d_sqrt = sqrt(form[D]);
		t1 = (-form[B] + d_sqrt) / (2 * form[A]);
		t2 = (-form[B] - d_sqrt) / (2 * form[A]);
		if (0 < t1 && (t1 < t2 || t2 <= 0))
			return (t1);
		else if (0 < t2)
			return (t2);
	}
	return (0);
}

static bool	intersection_test_sphere(const t_sphere *shpere, const t_ray *ray, t_intersection_point *out_intp)
{
	double	form[FORMULA_NUM];
	double	t;
	t_vec3	start_center;

	start_center = sub(ray->start, shpere->center);
	form[A] = squared_norm(&ray->direction);
	form[B] = 2 * dot(&start_center, &ray->direction);
	form[C] = squared_norm(&start_center) - SQR(shpere->diameter / 2);
	t = get_t(form);
	if (t > 0)
	{
		out_intp->distance = t * norm(&ray->direction);
		out_intp->pos = add(times(t, ray->direction), ray->start);
		out_intp->normal = sub(out_intp->pos, shpere->center);
		normalize(&out_intp->normal);
		return (true);
	}
	// need to complete
	return (false);
}

static bool	intersection_test_plane(const t_plane *plane, const t_ray *ray, t_intersection_point *out_intp)
{
	double dn_dot;
	double t;
	t_vec3 normal;

	normal = plane->norm_ori_vec;
	normalize(&normal);
	dn_dot = dot(&ray->direction, &normal);
	if (dn_dot != 0)
	{
		t = (dot(&plane->pos, &normal) - dot(&ray->start, &normal)) / dn_dot;
		if (t > 0)
		{
			out_intp->distance = t * norm(&ray->direction);
			out_intp->pos = add(times(t, ray->direction), ray->start);
			out_intp->normal = normal;
			return (true);
		}
	}
	// need to complete
	return (false);
}

static bool	intersection_test_cylinder(const t_cylinder *cylinder, const t_ray *ray, t_intersection_point *out_intp)
{
	(void)cylinder;
	(void)ray;
	(void)out_intp;
	// need to complete
	return (false);
}

bool intersection_test(const t_list *obj, const t_ray *ray, t_intersection_point *out_intp)
{
	if (obj->cont_type == Sphere)
		return (intersection_test_sphere(obj->content, ray, out_intp));
	if (obj->cont_type == Plane)
		return (intersection_test_plane(obj->content, ray, out_intp));
	if (obj->cont_type == Cylinder)
		return (intersection_test_cylinder(obj->content, ray, out_intp));
	return (false);
}
