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

typedef enum e_ctype
{
	RED,
	GREEN,
	BLUE,
	CTYPE_NUM
}	t_ctype;

double range(const t_color *c, t_ctype ctype)
{
	if (ctype == RED)
		return (c->r);
	if (ctype == GREEN)
		return (c->g);
	if (ctype == BLUE)
		return (c->b);
	return (0);
}

double	get_light_range(const t_world *w, const t_material *mat, const double norm_dot_inc, const t_ctype ctype)
{
	double	ambient_ref_light;
	double	diffuse_ref_light;
	double	specular_ref_light;

	ambient_ref_light = range(&mat->ambient_ref, ctype) * w->amb_light.ratio;//const
	if (norm_dot_inc > 0)
	{
		diffuse_ref_light = range(&mat->diffuse_ref, ctype) * norm_dot_inc;
		specular_ref_light = 
	}
}

void get_color(const t_world *w, const t_intersection_point *nearest_intp, const t_material *mat, t_color *out_col)
{
	t_vec3	incidence_vec;
	double	norm_dot_inc;

	incidence_vec = sub(w->light.pos, nearest_intp->pos);
	normalize(&incidence_vec);
	norm_dot_inc = dot(&nearest_intp->normal, &incidence_vec);
	out_col->r = get_light_range(w, mat, norm_dot_inc, RED);
	out_col->g = get_light_range(w, mat, norm_dot_inc, GREEN);
	out_col->b = get_light_range(w, mat, norm_dot_inc, BLUE);
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
	get_color(w, &nearest_intp, &mat, out_col);
	// need to complete
	return (true);
}
