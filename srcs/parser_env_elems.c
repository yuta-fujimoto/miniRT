#include "miniRT.h"

bool	parser_amb_light(t_world *w, char **info)
{
	if (ft_str_arr_len(info) != 3)
		return (false);
	if (!ft_atof(info[1], &w->amb_light.ratio)
		|| w->amb_light.ratio < 0 || w->amb_light.ratio > 1.0)
		return (false);
	if (!atocol(info[2], &w->amb_light.c))
		return (false);
	w->env_elems_exists[0] = true;
	return (true);
}

bool	parser_camera(t_world *w, char **info)
{
	if (ft_str_arr_len(info) != 4)
		return (false);
	if (!atovec3(info[1], &w->camera.pos))
		return (false);
	if (!atovec3(info[2], &w->camera.norm_ori_vec)
		|| !is_normed_vec(w->camera.norm_ori_vec))
		return (false);
	if (!ft_atoi(info[3], &w->camera.fov)
		|| w->camera.fov < 0 || w->camera.fov > 180)
		return (false);
	normalize(&w->camera.norm_ori_vec);
	w->env_elems_exists[1] = true;
	return (true);
}

bool	parser_light(t_world *w, char **info)
{
	if (ft_str_arr_len(info) != 3)
		return (false);
	if (!atovec3(info[1], &w->light.pos))
		return (false);
	if (!ft_atof(info[2], &w->light.ratio)
		|| w->light.ratio < 0 || w->light.ratio > 1.0)
		return (false);
	w->env_elems_exists[2] = true;
	return (true);
}
