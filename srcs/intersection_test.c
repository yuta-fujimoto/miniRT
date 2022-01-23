#include "miniRT.h"

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
		out_intp->pos = get_position(t, ray);
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
	t_vec3 start_origin;

	normal = plane->norm_ori_vec;
	normalize(&normal);
	start_origin = sub(ray->start, plane->norm_ori_vec);
	dn_dot = dot(&ray->direction, &normal);
	if (dn_dot != 0)
	{
		t = (dot(&plane->pos, &normal) - dot(&start_origin, &normal)) / dn_dot;
		if (t > 0)
		{
			out_intp->distance = t * norm(&ray->direction);
			out_intp->pos = get_position(t, ray);
			out_intp->normal = normal;
			return (true);
		}
	}
	// need to complete
	return (false);
}

static bool	intersection_test_cylinder(const t_cylinder *cylinder, const t_ray *ray, t_intersection_point *out_intp)
{
	t_ray	cyl_ray;
	double	form[FORMULA_NUM];
	int		t;
	double	height;

	cyl_ray.start = cross(cylinder->norm_ori_vec, sub(ray->start, cylinder->pos));
	cyl_ray.direction = cross(cylinder->norm_ori_vec, ray->direction);
	form[A] = squared_norm(&cyl_ray.direction);
	form[B] = 2 * dot(&cyl_ray.start, &cyl_ray.direction);
	form[C] = squared_norm(&cyl_ray.start) - SQR(cylinder->diameter / 2);
	if (get_t(form) <= 0)
		return (false);
	t = cylinder_height_test(cylinder, ray, form, &height);
	if (!t)
		return (false);
	out_intp->distance = form[t] * norm(&ray->direction);
	out_intp->pos = get_position(form[t], ray);
	out_intp->normal = sub(out_intp->pos, add(cylinder->pos, times(height, cylinder->norm_ori_vec)));
	normalize(&out_intp->normal);
	return (true);
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
