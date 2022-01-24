#include "miniRT.h"

bool	parse_line(char *line, t_world *w)
{
	char	**info;
	bool	rlt;

	if (!*line)
		return (true);
	info = ft_split(line, ' ');
	if (!info)
		return (false);
	rlt = false;
	if (ft_strequal("A", info[0], 2) && !w->env_elems_exists[0])
		rlt = parser_amb_light(w, info);
	else if (ft_strequal("C", info[0], 2) && !w->env_elems_exists[1])
		rlt = parser_camera(w, info);
	else if (ft_strequal("L", info[0], 2) && !w->env_elems_exists[2])
		rlt = parser_light(w, info);
	else if (ft_strequal("sp", info[0], 3))
		rlt = parser_sphere(w, info);
	else if (ft_strequal("pl", info[0], 3))
		rlt = parser_plane(w, info);
	else if (ft_strequal("cy", info[0], 3))
		rlt = parser_cylinder(w, info);
	else if (!info[0])
		rlt = true;
	ft_str_arr_free(info);
	return (rlt);
}

bool	parser_init(int *fd, char *fn, t_world *w)
{
	*fd = open(fn, O_RDONLY);
	if (*fd == -1)
		return (false);
	w->obj_list = NULL;
	w->env_elems_exists[0] = false;
	w->env_elems_exists[1] = false;
	w->env_elems_exists[2] = false;
	return (true);
}

bool	parser(char *fn, t_world *w)
{
	int		fd;
	char	*line;

	if (!parser_init(&fd, fn, w))
		return (NULL);
	while (get_next_line(fd, &line) != 0)
	{
		if (!line || !parse_line(line, w))
		{
			safe_free(line);
			return (end_world(w, false));
		}
		safe_free(line);
	}
	if (!line || !parse_line(line, w))
	{
		safe_free(line);
		return (end_world(w, false));
	}
	safe_free(line);
	if (!w->env_elems_exists[0] || !w->env_elems_exists[1]
		|| !w->env_elems_exists[2])
		return (end_world(w, false));
	return (true);
}
