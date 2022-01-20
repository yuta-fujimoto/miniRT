#include "miniRT.h"

// 影を付けるときにmax_distとexit_onde_foundの考慮をします。別関数にしましょう
static bool get_nearest_obj(const t_world *w, const t_ray *ray, t_list **out_obj, t_intersection_point *out_intp)
{
	t_list					*objs;
	t_intersection_point	p;

	objs = w->obj_list;
	out_intp->distance = LONG_MAX;
	while (objs)
	{
		if (intersection_test(objs, ray, &p) && out_intp->distance > p.distance)
		{
			*out_intp = p;
			*out_obj = objs;
		}
		objs = objs->next;
	}
	if (out_intp->distance == LONG_MAX)
		return (false);
	return (true);
}

void get_material(t_list *obj, t_material *mat)
{
	t_color	c;

	if (obj->cont_type == Sphere)
		c = ((t_sphere *)obj->content)->c;
	else if (obj->cont_type == Plane)
		c = ((t_plane *)obj->content)->c;
	else if (obj->cont_type == Cylinder)
		c = ((t_cylinder *)obj->content)->c;
	mat->ambient_ref = c;
	mat->diffuse_ref = c;
	mat->specular_ref = color(REF_FACTOR_MIRROR, REF_FACTOR_MIRROR, REF_FACTOR_MIRROR);
	mat->shininess = SHININESS;
}

bool raytrace(const t_world *w, const t_ray *cam_ray, t_color *out_col)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;

	if (!get_nearest_obj(w, cam_ray, &nearest_obj, &nearest_intp))
		return (false);
	out_col->r = 1.0;
	out_col->g = 0.0;
	out_col->b = 0.0;
	get_material(nearest_obj, &mat);
	// need to complete
	return (true);
}
