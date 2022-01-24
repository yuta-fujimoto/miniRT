#include "miniRT.h"

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = CLAMP(a->r, min, max);
	a->g = CLAMP(a->g, min, max);
	a->b = CLAMP(a->b, min, max);
}

void	add_color(const t_material *mat, t_refdata *refdata, t_color *out_col)
{
	t_color	diffuse_ref_light;
	t_color	specular_ref_light;
	double	pow_val;

	diffuse_ref_light = cmult(mat->diffuse_ref, \
						cmult(refdata->light_ratio, refdata->norm_dot_inc));
	refdata->reflection = \
		sub(times(2 * refdata->norm_dot_inc.r, refdata->normal), \
		refdata->incidence);
	normalize(&refdata->reflection);
	refdata->reverseray = times(-1, refdata->ray);
	normalize(&refdata->reverseray);
	pow_val = pow(dot(&refdata->reflection, &refdata->reverseray), \
					mat->shininess);
	specular_ref_light = cmult(mat->specular_ref, \
							cmult(refdata->light_ratio, \
							color(pow_val, pow_val, pow_val)));
	*out_col = cadd(*out_col, cadd(diffuse_ref_light, specular_ref_light));
	cfilter(out_col, 0, 1);
}
