#include "miniRT.h"

void	get_material(t_list *obj, t_material *mat)
{
	t_color		c;

	if (obj->cont_type == Sphere)
	{
		mat->type = ((t_sphere *)obj->content)->type;
		c = ((t_sphere *)obj->content)->c;
	}
	else if (obj->cont_type == Plane)
	{
		mat->type = ((t_plane *)obj->content)->type;
		c = ((t_plane *)obj->content)->c;
	}
	else if (obj->cont_type == Cylinder)
	{
		mat->type = ((t_cylinder *)obj->content)->type;
		c = ((t_cylinder *)obj->content)->c;
	}
	mat->ambient_ref = c;
	mat->diffuse_ref = c;
	mat->specular_ref = color(COEF_SPECULAR_REF, \
								COEF_SPECULAR_REF, COEF_SPECULAR_REF);
	mat->perfect_ref = color(COEF_PERFECT_REF, \
								COEF_PERFECT_REF, COEF_PERFECT_REF);
	mat->shininess = SHININESS;
}

bool	atomattype(char *s, t_mattype *type)
{
	*type = NORMAL;
	if (!s)
		return (true);
	if (ft_strequal(s, "SPECULAR", 9))
	{
		*type = SPECULAR;
		return (true);
	}
	else if (ft_strequal(s, "PERFECT", 8))
	{
		*type = PERFECT;
		return (true);
	}
	return (false);
}
