#include "miniRT.h"

double	sqr(double x)
{
	return (x * x);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	clamp(double v, double minv, double maxv)
{
	return (min(max(v, minv), maxv));
}
