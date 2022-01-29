#include "miniRT.h"

static void	*isnull(t_data *data, void *result)
{
	if (!result)
	{
		ft_putendl_fd("Error\nMlx malloc error", STDERR_FILENO);
		ft_exit(data, EXIT_FAILURE);
	}
	return (result);
}

void	data_init(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->w.obj_list = NULL;
	data->mlx = isnull(data, mlx_init());
	data->win = isnull(data, \
						mlx_new_window(data->mlx, \
							W_IMG, H_IMG, \
							"FYUTA in the house"));
	data->img = isnull(data, \
						mlx_new_image(data->mlx, W_IMG, H_IMG));
	data->addr = isnull(data, \
						mlx_get_data_addr(data->img, \
							&data->bits_per_pixel, \
							&data->line_length, \
							&data->endian));
}
