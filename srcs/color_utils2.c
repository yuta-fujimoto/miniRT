#include "miniRT.h"

t_color	ctimes(const double nb, const t_color c)
{
	return (color(nb * c.r, nb * c.g, nb * c.b));
}

t_color	c_zero(void)
{
	return (color(0, 0, 0));
}

t_color	c_background(void)
{
	return (color(1, 1, 1));
}
