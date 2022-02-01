#include "miniRT.h"

void	data_set(t_data *data)
{
	double		x_img;
	double		y_img;
	t_ray		camray;
	t_default	def;

	default_set(&data->w, &def);
	camray.start = data->w.camera.pos;
	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			camray.direction = to3axis(x_img, y_img, &def);
			my_mlx_pixel_put(data, (int)x_img, (int)y_img, \
								raytrace(&data->w, camray, 0));
			x_img++;
		}
		y_img++;
	}
}
