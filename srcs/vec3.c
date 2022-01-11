#include "miniRT.h"

static bool end_conversion(char **s, bool rlt)
{
	ft_str_arr_free(s);
	return (rlt);
}

bool atovec3(char const *nptr, t_vec3 *v)
{
	char	**vec3;

	v->x = 0;
	v->y = 0;
	v->z = 0;
	vec3 = ft_split(nptr, ',');
	if (ft_str_arr_len(vec3) != 3 || !vec3)
		return (end_conversion(vec3, false));
	if (!ft_atof(vec3[0], &v->x) || !ft_atof(vec3[1], &v->y) || !ft_atof(vec3[2], &v->z))
		return (end_conversion(vec3, false));
	return (end_conversion(vec3, true));
}

bool atocol(char const *nptr, t_color *c)
{
	char **rgb;

	c->r = 0;
	c->g = 0;
	c->b = 0;
	rgb = ft_split(nptr, ',');
	if (ft_str_arr_len(rgb) != 3 || !rgb)
		return (end_conversion(rgb, false));
	if (!ft_atoi(rgb[0], &c->r) || !ft_atoi(rgb[1], &c->g) || !ft_atoi(rgb[2], &c->b))
		return (end_conversion(rgb, false));
	if (c->r < 0 || c->r > 255 ||
		c->g < 0 || c->g > 255 || c->b < 0 || c->b > 255)
		return (end_conversion(rgb, false));
	return (end_conversion(rgb, true));
}

bool is_normalized_vector(t_vec3 v)
{
	return (v.x >= -1.0 && v.x <= 1.0 && v.y >= -1.0 
		&& v.y <= 1.0 && v.z >= -1.0 && v.z <= 1.0);
}
