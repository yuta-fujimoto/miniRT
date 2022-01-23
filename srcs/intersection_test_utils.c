#include "miniRT.h"

double	get_t(double form[FORMULA_NUM])
{
	double	d_sqrt;

	form[D] = SQR(form[B]) - (4 * form[A] * form[C]);
	if (form[D] >= 0)
	{
		d_sqrt = sqrt(form[D]);
		form[T1] = (-form[B] + d_sqrt) / (2 * form[A]);
		form[T2] = (-form[B] - d_sqrt) / (2 * form[A]);
		if (0 < form[T1] && (form[T1] < form[T2] || form[T2] <= 0))
			return (form[T1]);
		else if (0 < form[T2])
			return (form[T2]);
	}
	return (0);
}

t_vec3	get_position(const double t, const t_ray *ray)
{
	return (add(times(t, ray->direction), ray->start));
}

int	cylinder_height_test(const t_cylinder *cylinder, const t_ray *ray,
	const double form[FORMULA_NUM], double *out_height)
{
	t_vec3	v;
	double	height[2];

	v = sub(get_position(form[T1], ray), cylinder->pos);
	height[0] = dot(&v, &cylinder->norm_ori_vec);
	v = sub(get_position(form[T2], ray), cylinder->pos);
	height[1] = dot(&v, &cylinder->norm_ori_vec);
	if (fabs(height[0]) <= cylinder->height / 2.0 && form[T1] > 0 
		&& (form[T1] <= form[T2] || form[T2] <= 0
		|| fabs(height[1]) > (cylinder->height / 2.0)))
	{
		*out_height = height[0];
		return (T1);
	}
	if (fabs(height[1]) <= cylinder->height / 2.0 && form[T2] > 0)
	{
		*out_height = height[1];
		return (T2);
	}
	return (0);
}
