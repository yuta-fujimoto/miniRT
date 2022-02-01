#include "miniRT.h"

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = clamp(a->r, min, max);
	a->g = clamp(a->g, min, max);
	a->b = clamp(a->b, min, max);
}

t_color	c_ambient(const t_amb_light *a, const t_material *mat)
{
	return (cmult(mat->ambient_ref, ctimes(a->ratio, a->c)));
}

t_color	c_diffuse(const t_light *l, \
					const t_material *mat, const t_refdata *refdata)
{
	return (cmult(mat->diffuse_ref, \
				ctimes(refdata->dot_ni, ctimes(l->ratio, l->c))));
}

t_color	c_specular(const t_light *l, const t_material *mat, \
					const t_ray *cam_ray, t_refdata *refdata)
{
	t_vec3	reverseray;
	double	pow_val;

	if (mat->type != SPECULAR)
		return (color(0, 0, 0));
	reverseray = times(-1, cam_ray->direction);
	normalize(&reverseray);
	pow_val = pow(calc_toon(dot(&refdata->ref_vec, \
							&reverseray), refdata->use_toon), \
					mat->shininess);
	return (cmult(mat->specular_ref, \
				ctimes(pow_val, ctimes(l->ratio, l->c))));
}

t_color	obj_color(const t_world *w, const t_ray \
			*cam_ray, const t_intersection_point *intp, const t_material *mat)
{
	t_color		out_col;
	t_refdata	refdata;

	out_col = color(0, 0, 0);
	out_col = cadd(out_col, c_ambient(&w->amb_light, mat));
	if (intersection_test_light(w, ray(intp->pos, \
		sub(w->light.pos, intp->pos))))
		return (out_col);
	if (reflection_test(w, sub(intp->pos, w->light.pos), intp, &refdata))
	{
		out_col = cadd(out_col, c_diffuse(&w->light, mat, &refdata));
		out_col = cadd(out_col, c_specular(&w->light, mat, cam_ray, &refdata));
		cfilter(&out_col, 0, 1);
	}
	return (out_col);
}
