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

void get_refdata(const t_world *w, const t_ray *cam_ray, const t_intersection_point *intp, t_refdata *refdata)
{
	refdata->camray_vec = cam_ray->direction;
	refdata->normal_vec = intp->normal;
	refdata->incidence_vec = sub(w->light.pos, intp->pos);
	normalize(&refdata->incidence_vec);
	refdata->norm_dot_inc = dot(&refdata->normal_vec, &refdata->incidence_vec);
}

double pickc(const t_color *c, t_ctype ctype)
{
	if (ctype == RED)
		return (c->r);
	if (ctype == GREEN)
		return (c->g);
	if (ctype == BLUE)
		return (c->b);
	return (0);
}

// 計算の考え方は以下です
// Lr = La + Ld + Ls
// La = Ka(mat->ambient_ref) * Ea(w->amb_light.ratio)
// Ld = Kd(mat->diffuese_ref) * Ei(w->light.ratio) * dot(normal,incidence)
// Ls = Ks(mat->specular_ref) * Ei(w->light.ratio) * pow(dot(reflection,-ray), mat->shininess)
double	get_light(const t_world *w, t_refdata *refdata, const t_material *mat, const t_ctype ctype)
{
	double	ambient_ref_light;
	double	diffuse_ref_light;
	double	specular_ref_light;

	ambient_ref_light = pickc(&mat->ambient_ref, ctype) * w->amb_light.ratio;//const
	diffuse_ref_light = 0;
	specular_ref_light = 0;
	if (refdata->norm_dot_inc > 0)
	{
		diffuse_ref_light = pickc(&mat->diffuse_ref, ctype) * w->light.ratio * refdata->norm_dot_inc;
		refdata->reflection_vec = sub(times(2 * refdata->norm_dot_inc, refdata->normal_vec), refdata->incidence_vec);
		normalize(&refdata->reflection_vec);
		refdata->reverseray_vec = times(-1, refdata->camray_vec);
		normalize(&refdata->reverseray_vec);
		specular_ref_light = pickc(&mat->specular_ref, ctype) * w->light.ratio * \
								pow(dot(&refdata->reflection_vec, &refdata->reverseray_vec), mat->shininess);
	}
	return (ambient_ref_light + diffuse_ref_light + specular_ref_light);
}

// ここで光のrangeの件, 調整しようとしたんですが
// 出力する球が真っ黒になったり思い通りいかなかったので迷走しています
double	filter(double light)
{
	//if (light > 255)
	//	light = 255;
	//return (light / 255);
	return (light);
}

bool raytrace(const t_world *w, const t_ray *cam_ray, t_color *out_col)
{
	t_list					*nearest_obj;
	t_intersection_point	nearest_intp;
	t_material				mat;
	t_refdata				refdata;//get_light()で必要な情報をまとめるため追加

	if (!get_nearest_obj(w, cam_ray, &nearest_obj, &nearest_intp))
		return (false);
	if (intersection_test_light(w, ray(nearest_intp.pos,
		sub(w->light.pos, nearest_intp.pos))))
	{
		*out_col = color(0, 0, 0);
		return (true);
	}
	get_material(nearest_obj, &mat);
	get_refdata(w, cam_ray, &nearest_intp, &refdata);
	out_col->r = filter(get_light(w, &refdata, &mat, RED));
	out_col->g = filter(get_light(w, &refdata, &mat, GREEN));
	out_col->b = filter(get_light(w, &refdata, &mat, BLUE));
	// need to complete
	return (true);
}
