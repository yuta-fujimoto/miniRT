#include "miniRT.h"

bool	print_error(const int line_count, const t_error_status error_status)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (error_status == NOARG)
		ft_putendl_fd("Invalid number of arguments", STDERR_FILENO);
	else if (error_status == SYSERROR)
		perror(NULL);
	else if (error_status == NOENV)
		ft_putendl_fd("Lack environmental info(A,C,L)", STDERR_FILENO);
	else if (error_status == EFORMAT)
		ft_putendl_fd("Not a .rt file", STDERR_FILENO);
	else if (error_status == EPARSE)
	{
		ft_putstr_fd("Line ", STDERR_FILENO);
		ft_putnbr_fd(line_count, STDERR_FILENO);
		ft_putendl_fd(": failed to parse", STDERR_FILENO);
	}
	else
		return (true);
	return (false);
}
