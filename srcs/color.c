#include "miniRT.h"

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = clamp(a->r, min, max);
	a->g = clamp(a->g, min, max);
	a->b = clamp(a->b, min, max);
}

t_color	c_diffuse(const t_material *mat, const t_refdata *refdata)
{
	return (cmult(mat->diffuse_ref, ctimes(refdata->dot_ni, refdata->light_attr)));
}

t_color	c_specular(const t_material *mat, const t_ray *cam_ray, t_refdata *refdata)
{
	t_vec3	reverseray;
	double	pow_val;

	reverseray = times(-1, cam_ray->direction);
	normalize(&reverseray);
	pow_val = pow(calc_toon(dot(&refdata->ref_vec, \
							&reverseray), refdata->use_toon), \
					mat->shininess);
	return (cmult(mat->specular_ref, \
				ctimes(pow_val, refdata->light_attr)));
}
