#include "miniRT.h"

t_color	cmult(const t_color a, const t_color b)
{
	return (color(a.r * b.r, a.g * b.g, a.b * b.b));
}

t_color	cadd(const t_color a, const t_color b)
{
	return (color(a.r + b.r, a.g + b.g, a.b + b.b));
}

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
