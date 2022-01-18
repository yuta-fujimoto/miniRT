#include "miniRT.h"

static bool	intersection_test_sphere(const t_sphere *shpere, const t_ray *ray, t_intersection_point *out_intp)
{
	(void)shpere;
	(void)ray;
	(void)out_intp;
	// need to complete
	return (false);
}

static bool	intersection_test_plane(const t_plane *plane, const t_ray *ray, t_intersection_point *out_intp)
{
	double dn_dot;
	double t;

	dn_dot = dot(&ray->direction, &plane->norm_ori_vec);
	if (dn_dot != 0)
	{
		t = (dot(&plane->pos, &plane->norm_ori_vec) - dot(&ray->start, &plane->norm_ori_vec)) / dn_dot;
		if (t > 0)
		{
			out_intp->distance = t * norm(&ray->direction);
			out_intp->position = vec3sigma(t, ray->direction, 1, ray->start);
			out_intp->normal = plane->norm_ori_vec;
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
