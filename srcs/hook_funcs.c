#include "miniRT.h"

int	ft_exit(t_data *data, int status)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->w.obj_list)
		ft_lstclear(&data->w.obj_list, free);
	exit(status);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_ESCAPE)
		ft_exit(data, EXIT_SUCCESS);
	return (0);
}

int	close_window(t_data *data)
{
	ft_exit(data, EXIT_SUCCESS);
	return (0);
}
