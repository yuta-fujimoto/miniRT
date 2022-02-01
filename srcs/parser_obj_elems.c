#include "miniRT.h"

static bool	parser_obj_failure(void *p)
{
	free(p);
	return (false);
}

bool	parser_sphere(t_world *world, char **info)
{
	t_sphere	*s;
	int			str_arr_len;

	str_arr_len = ft_str_arr_len(info);
	if (str_arr_len != 4 && str_arr_len != 5)
		return (false);
	s = malloc(sizeof(t_sphere));
	if (!s)
		return (s);
	if (!atovec3(info[1], &s->center))
		return (parser_obj_failure(s));
	if (!ft_atof(info[2], &s->diameter) || s->diameter <= 0)
		return (parser_obj_failure(s));
	if (!atocol(info[3], &s->c))
		return (parser_obj_failure(s));
	if (!atomattype(info[4], &s->type))
		return (parser_obj_failure(s));
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(s, Sphere)))
		return (parser_obj_failure(s));
	return (true);
}

bool	parser_plane(t_world *world, char **info)
{
	t_plane	*p;
	int		str_arr_len;

	str_arr_len = ft_str_arr_len(info);
	if (str_arr_len != 4 && str_arr_len != 5)
		return (false);
	p = malloc(sizeof(t_plane));
	if (!p)
		return (p);
	if (!atovec3(info[1], &p->pos))
		return (parser_obj_failure(p));
	if (!atovec3(info[2], &p->norm_ori_vec) || !is_normed_vec(p->norm_ori_vec))
		return (parser_obj_failure(p));
	if (!atocol(info[3], &p->c))
		return (parser_obj_failure(p));
	if (!atomattype(info[4], &p->type))
		return (parser_obj_failure(p));
	normalize(&p->norm_ori_vec);
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(p, Plane)))
		return (parser_obj_failure(p));
	return (true);
}

bool	parser_cylinder(t_world *world, char **info)
{
	t_cylinder	*c;
	int			str_arr_len;

	str_arr_len = ft_str_arr_len(info);
	if (str_arr_len != 6 && str_arr_len != 7)
		return (false);
	c = malloc(sizeof(t_cylinder));
	if (!c)
		return (c);
	if (!atovec3(info[1], &c->pos))
		return (parser_obj_failure(c));
	if (!atovec3(info[2], &c->norm_ori_vec) || !is_normed_vec(c->norm_ori_vec))
		return (parser_obj_failure(c));
	if (!ft_atof(info[3], &c->diameter) || c->diameter <= 0)
		return (parser_obj_failure(c));
	if (!ft_atof(info[4], &c->height) || c->height <= 0)
		return (parser_obj_failure(c));
	if (!atocol(info[5], &c->c))
		return (parser_obj_failure(c));
	if (!atomattype(info[6], &c->type))
		return (parser_obj_failure(c));
	normalize(&c->norm_ori_vec);
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(c, Cylinder)))
		return (parser_obj_failure(c));
	return (true);
}
