#include "miniRT.h"

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = clamp(a->r, min, max);
	a->g = clamp(a->g, min, max);
	a->b = clamp(a->b, min, max);
}

void	add_color(const t_material *mat, t_refdata *refdata, t_color *out_col)
{
	t_color	diffuse_ref_light;
	t_color	specular_ref_light;
	t_vec3	ref_vec;
	t_vec3	reverseray_vec;
	double	pow_val;

	diffuse_ref_light = cmult(mat->diffuse_ref, \
						ctimes(refdata->norm_dot_inc, refdata->light_attr));
	ref_vec = \
		sub(times(2 * refdata->norm_dot_inc, refdata->normal), \
		refdata->incidence);
	normalize(&ref_vec);
	reverseray_vec = times(-1, refdata->ray);
	normalize(&reverseray_vec);
	pow_val = pow(calc_toon(dot(&ref_vec, &reverseray_vec), \
		refdata->use_toon), mat->shininess);
	specular_ref_light = cmult(mat->specular_ref, \
							ctimes(pow_val, refdata->light_attr));
	*out_col = cadd(*out_col, cadd(diffuse_ref_light, specular_ref_light));
	cfilter(out_col, 0, 1);
}
