#include "miniRT.h"

double	calc_toon(double dot, bool use_toon)
{
	if (!use_toon)
		return (dot);
	return (ceil(TOON_LEVEL * (1 - (2 / M_PI) * acos(dot))) / TOON_LEVEL);
}

bool	toon_edge(t_vec3 norm, t_vec3 dir, t_list *obj)
{
	double	thickness;

	if (obj->cont_type == Plane)
		thickness = TOON_EDGE_THICKNESS_PLANE;
	else
		thickness = TOON_EDGE_THICKNESS;
	normalize(&dir);
	if (fabs(dot(&norm, &dir)) > thickness)
		return (false);
	return (true);
}

bool	atotoon(char *s, bool *use_toon)
{
	*use_toon = false;
	if (!s)
		return (true);
	if (ft_strequal(s, "TOON", 5))
	{
		*use_toon = true;
		return (true);
	}
	return (false);
}
