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

void	get_material(t_list *obj, t_material *mat)
{
	t_color		c;
	t_mattype	t;

	if (obj->cont_type == Sphere)
	{
		t = ((t_sphere *)obj->content)->type;
		c = ((t_sphere *)obj->content)->c;
	}
	else if (obj->cont_type == Plane)
	{
		t = ((t_plane *)obj->content)->type;
		c = ((t_plane *)obj->content)->c;
	}
	else if (obj->cont_type == Cylinder)
	{
		t = ((t_cylinder *)obj->content)->type;
		c = ((t_cylinder *)obj->content)->c;
	}
	mat->type = t;
	mat->ambient_ref = c;
	mat->diffuse_ref = c;
	mat->specular_ref = color(COEF_SPECULAR_REF, \
								COEF_SPECULAR_REF, COEF_SPECULAR_REF);
	mat->perfect_ref = color(COEF_PERFECT_REF, \
								COEF_PERFECT_REF, COEF_PERFECT_REF);
	mat->shininess = SHININESS;
	//mat->type = SPECULAR;
	//if (obj->cont_type == Sphere)
	//	mat->type = PERFECT;
}

bool	intersection_test_light(const t_world *w, t_ray shadow_ray)
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

bool	reflection_test(const t_world *w, const t_vec3 incidence, \
				const t_intersection_point *intp, t_refdata *refdata)
{
	refdata->norm_vec = intp->normal;
	refdata->pos = intp->pos;
	refdata->in_vec = times(-1, incidence);
	normalize(&refdata->in_vec);
	refdata->use_toon = w->light.use_toon;
	refdata->dot_ni = calc_toon(dot(&refdata->norm_vec, \
							&refdata->in_vec), refdata->use_toon);
	if (refdata->dot_ni <= 0)
		return (false);
	refdata->ref_vec = sub(times(2 * refdata->dot_ni, refdata->norm_vec), \
								refdata->in_vec);
	normalize(&refdata->ref_vec);
	return (true);
}

t_color	raytrace(const t_world *w, const t_ray cam_ray, int recursion_level)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;
	t_refdata				refdata;

	if (MAX_RECURSION < recursion_level)
		return (c_zero());
	if (!get_nearest_obj(w, &cam_ray, &nearest_obj, &nearest_intp))
		return (c_background());
	if (w->light.use_toon
		&& toon_edge(nearest_intp.normal, cam_ray.direction, nearest_obj))
		return (c_zero());
	get_material(nearest_obj, &mat);
	if (mat.type == PERFECT && \
		reflection_test(w, cam_ray.direction, &nearest_intp, &refdata))
	{
		refdata.pos = add(refdata.pos, times(EPSILON, refdata.ref_vec));
		return (cmult(mat.perfect_ref, \
						raytrace(w, ray(refdata.pos, refdata.ref_vec), \
												recursion_level + 1)));
	}
	return (obj_color(w, &cam_ray, &nearest_intp, &mat));
}
