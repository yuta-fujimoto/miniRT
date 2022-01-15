#include "mlx.h"
#include "tutorial.h"
#include <stdio.h>
#include <stdbool.h>

#define W_IMG 500
#define H_IMG 500

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vec3 conv2to3(double x_img, double y_img)
{
	t_vec3	vec_onscrn;
	double	w_scrn = 2;
	double	h_scrn = 2;

	vec_onscrn.x = w_scrn * (x_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn.y = h_scrn * (y_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn.z = 0;
	return (vec_onscrn);
}

bool is_crossed(double x_img, double y_img, t_vecs *vecs)
{
	vecs->vec_onscrn = conv2to3(x_img, y_img);
	vecs->vec_ray = sub(&(vecs->vec_onscrn), &(vecs->vec_view));
	double		A = squared_norm(&(vecs->vec_ray));
	double		B = 2 * dot(&(vecs->vec_ctr_to_view), &(vecs->vec_ray));
	double		C = squared_norm(&(vecs->vec_ctr_to_view)) - SQR(vecs->radius);
	double		D = B * B - 4 * A * C;
	if (D >= 0)
		return (true);
	else
		return (false);
}

int	main(void)
{
	t_data	data;
	t_vecs	vecs;
	double	x_img;
	double	y_img;
	int		color;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W_IMG, H_IMG, "Defence Line");
	data.img = mlx_new_image(data.mlx, W_IMG, H_IMG);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	vecs.vec_view = vec3(0.0, 0.0, -5.0);
	vecs.vec_ctr = vec3(0.0, 0.0, 5.0);
	vecs.vec_ctr_to_view = sub(&(vecs.vec_view), &(vecs.vec_ctr));
	vecs.radius = 1.0;

	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			if (is_crossed(x_img, y_img, &vecs))
				color = GREEN;
			else
				color = BLUE;
			my_mlx_pixel_put(&data,(int)x_img, (int)y_img, color);
			x_img++;
		}
		y_img++;
	}

	mlx_hook(data.mlx_win, 33, 1 << 17, ft_exit, &data);
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
