#include "tutorial.h"
#include "mlx.h"

int ft_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);

	exit(0);
}

int key_hook(int keycode, t_data *data)
{
	if (keycode == XK_ESCAPE)
		ft_exit(data);
	return (0);
}
