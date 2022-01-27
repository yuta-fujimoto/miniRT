#include "miniRT.h"

t_color	ctimes(const double nb, const t_color c)
{
	return (color(nb * c.r, nb * c.g, nb * c.b));
}
