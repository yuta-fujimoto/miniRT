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
	mat->perfect_ref = color(COEF_PERFECT_REF, \
								COEF_PERFECT_REF, COEF_PERFECT_REF);
	mat->shininess = SHININESS;
	mat->mattype = SPECULAR;
	if (obj->cont_type == Sphere)
		mat->mattype = PERFECT;
}

bool	reflection_test(const t_world *w, const t_vec3 incidence, const t_intersection_point *intp, t_refdata *refdata)
{
	refdata->norm_vec = intp->normal;
	refdata->pos = intp->pos;
	refdata->in_vec = times(-1, incidence);
	normalize(&refdata->in_vec);
	refdata->use_toon = w->light.use_toon;
	refdata->dot_ni = calc_toon(dot(&refdata->norm_vec, &refdata->in_vec), refdata->use_toon);
	if (refdata->dot_ni <= 0)
		return (false);
	refdata->ref_vec = sub(times(2 * refdata->dot_ni, refdata->norm_vec), refdata->in_vec);
	normalize(&refdata->ref_vec);
	return (true);
}

bool	raytrace(const t_world *w, const t_ray *cam_ray, t_color *out_col, int recursion_level)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;
	t_refdata				refdata;

	if (MAX_RECURSION < recursion_level)
		return (true);
	if (!get_nearest_obj(w, cam_ray, &nearest_obj, &nearest_intp))
		return (false);
	if (toon_edge(nearest_intp.normal, cam_ray->direction, out_col, w->light.use_toon))
		return (true);
	get_material(nearest_obj, &mat);
	*out_col = cadd(*out_col, c_ambient(&w->amb_light, &mat));
	if (mat.mattype != PERFECT && !intersection_test_light(w, ray(nearest_intp.pos, \
		sub(w->light.pos, nearest_intp.pos))) && \
		reflection_test(w, sub(nearest_intp.pos, w->light.pos), &nearest_intp, &refdata))
	{
		*out_col = cadd(*out_col, c_diffuse(&w->light, &mat, &refdata));
		*out_col = cadd(*out_col, c_specular(&w->light, &mat, cam_ray, &refdata));
		cfilter(out_col, 0, 1);
	}
	if (mat.mattype == PERFECT && reflection_test(w, cam_ray->direction, &nearest_intp, &refdata))
	{
		t_color	recursion_col = color(0, 0, 0);
		refdata.pos = add(refdata.pos, times(EPSILON, refdata.ref_vec));
		t_ray recursion_ray = ray(refdata.pos, refdata.ref_vec);
		raytrace(w, &recursion_ray, &recursion_col, recursion_level + 1);
		*out_col = cadd(*out_col, cmult(mat.perfect_ref, recursion_col));
		cfilter(out_col, 0, 1);
	}
	return (true);
}
