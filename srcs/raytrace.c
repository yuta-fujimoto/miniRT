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

static bool intersection_test_light(const t_world *w, t_ray shadow_ray)
{
	t_list					*objs;
	t_intersection_point	p;
	double					distance;

	objs = w->obj_list;
	distance = normalize(&shadow_ray.direction) - EPSILON;
	shadow_ray.start = add(shadow_ray.start, times(EPSILON, shadow_ray.direction));
	while (objs)
	{
		if (intersection_test(objs, &shadow_ray, &p) && distance > p.distance)
			return (true);
		objs = objs->next;
	}
	return (false);
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

bool reflection_test(const t_world *w, const t_ray *cam_ray, const t_intersection_point *intp, t_refdata *out_data)
{
	double	dot_val;

	out_data->ray = cam_ray->direction;
	out_data->normal = intp->normal;
	out_data->incidence = sub(w->light.pos, intp->pos);
	normalize(&out_data->incidence);
	dot_val = dot(&out_data->normal, &out_data->incidence);
	if (dot_val <= 0)
		return (false);
	out_data->norm_dot_inc = color(dot_val, dot_val, dot_val);
	out_data->light_ratio = color(w->light.ratio, w->light.ratio, w->light.ratio);
	return (true);
}

void	add_color(const t_material *mat, t_refdata *refdata, t_color *out_col)
{
	t_color	diffuse_ref_light;
	t_color	specular_ref_light;
	double	pow_val;

	diffuse_ref_light = cmult(mat->diffuse_ref, cmult(refdata->light_ratio ,refdata->norm_dot_inc));
	refdata->reflection = sub(times(2 * refdata->norm_dot_inc.r, refdata->normal), refdata->incidence);
	normalize(&refdata->reflection);
	refdata->reverseray = times(-1, refdata->ray);
	normalize(&refdata->reverseray);
	pow_val = pow(dot(&refdata->reflection, &refdata->reverseray), mat->shininess);
	specular_ref_light = cmult(mat->specular_ref, cmult(refdata->light_ratio, color(pow_val, pow_val, pow_val)));
	*out_col = cadd(*out_col, cadd(diffuse_ref_light, specular_ref_light));
	cfilter(out_col, 0, 1);
}

bool raytrace(const t_world *w, const t_ray *cam_ray, t_color *out_col)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;
	t_refdata				refdata;

	if (!get_nearest_obj(w, cam_ray, &nearest_obj, &nearest_intp))
		return (false);
	get_material(nearest_obj, &mat);
	*out_col = cmult(mat.ambient_ref, \
				color(w->amb_light.ratio, w->amb_light.ratio, w->amb_light.ratio));
	if (intersection_test_light(w, ray(nearest_intp.pos,
		sub(w->light.pos, nearest_intp.pos))))
		return (true);
	if (reflection_test(w, cam_ray, &nearest_intp, &refdata))
		add_color(&mat, &refdata, out_col);
	// need to complete
	return (true);
}
