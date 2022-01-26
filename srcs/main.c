#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color dcolor)
{
	char	*dst;
	int		icolor;

	icolor = ((int)(dcolor.r * 255) << 16) | \
				((int)(dcolor.g * 255) << 8) | \
				(int)(dcolor.b * 255);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = icolor;
}

t_vec3	vec_cam_to_scrn(const double x_img, \
					const double y_img, const t_default *d)
{
	double			coef_dx;
	double			coef_dy;

	coef_dx = (W_SCRN * (x_img / d->max_xi)) - d->half_ws;
	coef_dy = (-d->h_scrn * (y_img / d->max_yi)) + d->half_hs;
	return (add(times(d->coef_n, d->cam.norm_ori_vec), \
			add(times(coef_dx, d->vec_dx), \
				times(coef_dy, d->vec_dy))));
}

int	main(int ac, char **av)
{
	t_world		w;
	t_default	d;
	t_ray		camray;
	t_data		data;
	double		x_img;
	double		y_img;
	t_color		col;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W_IMG, H_IMG, "Defence Line");
	data.img = mlx_new_image(data.mlx, W_IMG, H_IMG);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	if (ac != 2)
		return (print_error(0, NOARG));
	if (!parser(av[1], &w))
		return (0);
	print_world(&w);

	d.cam = w.camera;
	d.vec_ey = vec3(0, 1, 0);
	d.vec_dx = cross(d.vec_ey, d.cam.norm_ori_vec);
	normalize(&d.vec_dx);
	d.vec_dy = cross(d.cam.norm_ori_vec, d.vec_dx);
	normalize(&d.vec_dy);
	d.coef_n = W_SCRN / (2 * tan(radians((double)d.cam.fov / 2)));
	d.max_xi = W_IMG - 1;
	d.max_yi = H_IMG - 1;
	d.h_scrn = H_IMG * W_SCRN / W_IMG;
	d.half_ws = W_SCRN / 2;
	d.half_hs = d.h_scrn / 2;

	camray.start = w.camera.pos;
	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			camray.direction = vec_cam_to_scrn(x_img, y_img, &d);
			if (!raytrace(&w, &camray, &col))
				col = color(1.0, 1.0, 1.0);
			my_mlx_pixel_put(&data, (int)x_img, (int)y_img, col);
			x_img++;
		}
		y_img++;
	}

	mlx_hook(data.mlx_win, 33, 1 << 17, ft_exit, &data);
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
