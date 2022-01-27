#include "miniRT.h"

static bool	extension_equal(char *fn, char *ext)
{
	return (ft_strequal(ft_strrchr(fn, '.'), ext, ft_strlen(ext) + 1));
}

static bool	end_parse(int fd, t_error_status status, int line_count)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) == 1)
		safe_free(line);
	safe_free(line);
	if (fd != -1)
		close(fd);
	if (status != SUCCESS)
	{
		print_error(line_count, status);
		return (false);
	}
	return (true);
}

static bool	parse_line(char *line, t_world *w)
{
	char	**info;
	bool	rlt;

	info = ft_split(line, ' ');
	safe_free(line);
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

static bool	parser_init(int *fd, char *fn, t_world *w)
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
	int			fd;
	char		*line;
	static int	line_count = 1;
	int			gnl_status;

	if (!extension_equal(fn, ".rt"))
		return (end_parse(-1, EFORMAT, 0));
	if (!parser_init(&fd, fn, w))
		return (end_parse(fd, SYSERROR, 0));
	gnl_status = get_next_line(fd, &line);
	while (gnl_status != 0)
	{
		if (gnl_status == -1)
			return (end_parse(fd, SYSERROR, 0));
		if (!parse_line(line, w))
			return (end_parse(fd, EPARSE, line_count));
		line_count++;
		gnl_status = get_next_line(fd, &line);
	}
	if (!parse_line(line, w))
		return (end_parse(fd, EPARSE, line_count));
	if (!w->env_elems_exists[0] || !w->env_elems_exists[1]
		|| !w->env_elems_exists[2])
		return (end_parse(fd, NOENV, 0));
	return (end_parse(fd, SUCCESS, 0));
}
