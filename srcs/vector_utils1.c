#include "miniRT.h"

static bool	end_conversion(char **s, bool rlt)
{
	ft_str_arr_free(s);
	return (rlt);
}

t_vec3	vec3(const double x, const double y, const double z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

bool	atovec3(char const *nptr, t_vec3 *v)
{
	char	**vec3;

	v->x = 0;
	v->y = 0;
	v->z = 0;
	vec3 = ft_split(nptr, ',');
	if (ft_str_arr_len(vec3) != 3 || !vec3)
		return (end_conversion(vec3, false));
	if (!ft_atof(vec3[0], &v->x) || \
		!ft_atof(vec3[1], &v->y) || !ft_atof(vec3[2], &v->z))
		return (end_conversion(vec3, false));
	return (end_conversion(vec3, true));
}

bool	is_normed_vec(t_vec3 v)
{
	return (v.x >= -1.0 && v.x <= 1.0 && v.y >= -1.0 \
		&& v.y <= 1.0 && v.z >= -1.0 && v.z <= 1.0);
}
