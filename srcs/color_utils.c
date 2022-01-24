#include "miniRT.h"

static bool	end_conversion(char **s, bool rlt)
{
	ft_str_arr_free(s);
	return (rlt);
}

t_color	color(double r, double g, double b)
{
	t_color	rlt;

	rlt.r = r;
	rlt.g = g;
	rlt.b = b;
	return (rlt);
}

bool	atocol(char const *nptr, t_color *c)
{
	char	**rgb;
	int		icolor[3];

	icolor[0] = 0;
	icolor[1] = 0;
	icolor[2] = 0;
	rgb = ft_split(nptr, ',');
	if (ft_str_arr_len(rgb) != 3 || !rgb)
		return (end_conversion(rgb, false));
	if (!ft_atoi(rgb[0], &icolor[0]) || !ft_atoi(rgb[1], &icolor[1]) || !ft_atoi(rgb[2], &icolor[2]))
		return (end_conversion(rgb, false));
	if (icolor[0] < 0 || icolor[0] > 255 ||
		icolor[1] < 0 || icolor[1] > 255 || icolor[2] < 0 || icolor[2] > 255)
		return (end_conversion(rgb, false));
	*c = color(icolor[0] / 255.0, icolor[1] / 255.0, icolor[2] / 255.0);
	return (end_conversion(rgb, true));
}

t_color	cmult(const t_color a, const t_color b)
{
	t_color	ret;

	ret.r = a.r * b.r;
	ret.g = a.g * b.g;
	ret.b = a.b * b.b;
	return (ret);
}

t_color	cadd(const t_color a, const t_color b)
{
	t_color	ret;

	ret.r = a.r + b.r;
	ret.g = a.g + b.g;
	ret.b = a.b + b.b;
	return (ret);
}

void	cfilter(t_color *a, const double min, const double max)
{
	a->r = CLAMP(a->r, min, max);
	a->g = CLAMP(a->g, min, max);
	a->b = CLAMP(a->b, min, max);
}
