#include "miniRT.h"

int	main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		return (print_error(0, NOARG));
	data_init(&data);
	if (!parser(av[1], &data.w))
		ft_exit(&data, 0);
	print_world(&data.w);
	data_set(&data);
	mlx_hook(data.win, 33, 1 << 17, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
