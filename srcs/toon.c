#include "miniRT.h"

double	calc_toon(double dot, bool use_toon)
{
	if (!use_toon)
		return (dot);
	return (ceil(TOON_LEVEL * (1 - (2 / M_PI) * acos(dot))) / TOON_LEVEL);
}

bool	toon_edge(t_vec3 norm, t_vec3 dir, t_color *out_col, bool use_toon)
{
	if (!use_toon)
		return (false);
	normalize(&dir);
	if (fabs(dot(&norm, &dir)) > TOON_EDGE_THICKNESS)
		return (false);
	(void)out_col;
	//*out_col = color(0, 0, 0);
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
