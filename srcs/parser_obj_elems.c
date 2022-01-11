#include "miniRT.h"

static bool parser_obj_failure(void *p)
{
	free(p);
	return (false);
}

bool parser_sphere(t_world *world, char **info)
{
	t_sphere *s;

	if (ft_str_arr_len(info) != 4)
		return (false);
	s = malloc(sizeof(t_sphere));
	if (!s)
		return (s);
	if (!atovec3(info[1], &s->center))
		return (parser_obj_failure(s));
	if (!ft_atof(info[2], &s->diameter))
		return (parser_obj_failure(s));
	if (!atocol(info[3], &s->c))
		return (parser_obj_failure(s));
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(s, Sphere)))
		return (parser_obj_failure(s));
	return (true);
}

bool parser_plane(t_world *world, char **info)
{
	t_plane *p;

	if (ft_str_arr_len(info) != 4)
		return (false);
	p = malloc(sizeof(t_plane));
	if (!p)
		return (p);
	if (!atovec3(info[1], &p->pos))
		return (parser_obj_failure(p));
	if (!atovec3(info[2], &p->norm_ori_vec) || !is_normalized_vector(p->norm_ori_vec))
		return (parser_obj_failure(p));
	if (!atocol(info[3], &p->c))
		return (parser_obj_failure(p));
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(p, Plane)))
		return (parser_obj_failure(p));
	return (true);
}

bool parser_cylinder(t_world *world, char **info)
{
	t_cylinder *c;

	if (ft_str_arr_len(info) != 6)
		return (false);
	c = malloc(sizeof(t_cylinder));
	if (!c)
		return (c);
	if (!atovec3(info[1], &c->pos))
		return (parser_obj_failure(c));
	if (!atovec3(info[2], &c->norm_ori_vec) || !is_normalized_vector(c->norm_ori_vec))
		return (parser_obj_failure(c));
	if (!ft_atof(info[3], &c->diameter))
		return (parser_obj_failure(c));
	if (!ft_atof(info[4], &c->height))
		return (parser_obj_failure(c));
	if (!atocol(info[5], &c->c))
		return (parser_obj_failure(c));
	if (!ft_lstadd_back(&world->obj_list, ft_lstnew(c, Cylinder)))
		return (parser_obj_failure(c));
	return (true);
}
