#include "miniRT.h"

int main(int ac, char **av)
{
	t_world *w;

	if (ac != 2)
		return (0);
	w = parser(av[1]);
	if (!w)
	{
		write(STDERR_FILENO, "ERROR\n", 6);
		return (0);
	}
	print_world(w);
	end_world(w);
}
