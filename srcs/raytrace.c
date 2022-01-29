#include "miniRT.h"

static bool	get_nearest_obj(const t_world *w, const t_ray *ray, \
					t_list **out_obj, t_intersection_point *out_intp)
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

static bool	intersection_test_light(const t_world *w, t_ray shadow_ray)
{
	t_list					*objs;
	t_intersection_point	p;
	double					distance;

	objs = w->obj_list;
	distance = normalize(&shadow_ray.direction) - EPSILON;
	shadow_ray.start = add(shadow_ray.start, \
						times(EPSILON, shadow_ray.direction));
	while (objs)
	{
		if (intersection_test(objs, &shadow_ray, &p)
			&& (long)distance > (long)p.distance)
			return (true);
		objs = objs->next;
	}
	return (false);
}

void	get_material(t_list *obj, t_material *mat)
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
	mat->specular_ref = color(COEF_SPECULAR_REF, \
								COEF_SPECULAR_REF, COEF_SPECULAR_REF);
	mat->shininess = SHININESS;
}

bool	reflection_test(const t_world *w, const t_ray *cam_ray, \
					const t_intersection_point *intp, t_refdata *refdata)
{
	refdata->ray = cam_ray->direction;
	refdata->normal = intp->normal;
	refdata->incidence = sub(w->light.pos, intp->pos);
	normalize(&refdata->incidence);
	refdata->use_toon = w->light.use_toon;
	refdata->norm_dot_inc = calc_toon(dot(&refdata->normal, &refdata->incidence), refdata->use_toon);
	if (refdata->norm_dot_inc <= 0)
		return (false);
	refdata->light = ctimes(w->light.ratio, w->light.c);
	return (true);
}

bool	raytrace(const t_world *w, const t_ray *cam_ray, t_color *out_col)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;
	t_refdata				refdata;

	if (!get_nearest_obj(w, cam_ray, &nearest_obj, &nearest_intp))
		return (false);
	if (toon_edge(nearest_intp.normal, cam_ray->direction, out_col, w->light.use_toon))
		return (true);
	get_material(nearest_obj, &mat);
	*out_col = cmult(mat.ambient_ref, \
				ctimes(w->amb_light.ratio, w->amb_light.c));
	if (intersection_test_light(w, ray(nearest_intp.pos, \
		sub(w->light.pos, nearest_intp.pos))))
		return (true);
	if (reflection_test(w, cam_ray, &nearest_intp, &refdata))
		add_color(&mat, &refdata, out_col);
	return (true);
}
