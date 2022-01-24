#include "miniRT.h"

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = CLAMP(a->r, min, max);
	a->g = CLAMP(a->g, min, max);
	a->b = CLAMP(a->b, min, max);
}
