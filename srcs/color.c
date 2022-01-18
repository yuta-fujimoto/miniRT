#include "miniRT.h"

static bool end_conversion(char **s, bool rlt)
{
	ft_str_arr_free(s);
	return (rlt);
}

bool atocol(char const *nptr, t_color *c)
{
	char **rgb;
	int color[3];

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	rgb = ft_split(nptr, ',');
	if (ft_str_arr_len(rgb) != 3 || !rgb)
		return (end_conversion(rgb, false));
	if (!ft_atoi(rgb[0], &color[0]) || !ft_atoi(rgb[1], &color[1]) || !ft_atoi(rgb[2], &color[2]))
		return (end_conversion(rgb, false));
	if (color[0] < 0 || color[0] > 255 ||
		color[1] < 0 || color[1] > 255 || color[2] < 0 || color[2] > 255)
		return (end_conversion(rgb, false));
	c->r = color[0] / 255;
	c->g = color[1] / 255;
	c->b = color[2] / 255;
	return (end_conversion(rgb, true));
}

t_color color(double r, double g, double b)
{
	t_color	rlt;

	rlt.r = r;
	rlt.g = g;
	rlt.b = b;
	return (rlt);
}
