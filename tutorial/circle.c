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

t_vec3	conv2to3(double x_img, double y_img)
{
	t_vec3	vec_onscrn;
	double	w_scrn = 2;
	double	h_scrn = 2;

	vec_onscrn.x = w_scrn * (x_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn.y = h_scrn * (y_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn.z = 0;
	return (vec_onscrn);
}

double	cal_t(double a, double b, double d)
{
	double	d_sqrt;
	double	mol1;
	double	mol2;

	if (d >= 0)
	{
		d_sqrt = sqrt(d);
		mol1 = -b + d_sqrt;
		mol2 = -b - d_sqrt;
		if (0 < mol1 && mol1 < mol2)
			return (mol1 / 2 * a);
		else if (0 < mol2)
			return (mol2 / 2 * a);
	}
	return (-1);
}

int	raytrace(double x_img, double y_img, t_info *info)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t;

	info->vec_onscrn = conv2to3(x_img, y_img);
	info->vec_ray = sub(&(info->vec_onscrn), &(info->vec_view));
	a = squared_norm(&(info->vec_ray));
	b = 2 * dot(&(info->vec_ctr_to_view), &(info->vec_ray));
	c = info->buf;
	d = SQR(b) - 4 * a * c;
	t = cal_t(a, b, d);
	if (t > 0)
		return (GREEN);
	return (BLUE);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, W_IMG, H_IMG, "Defence Line");
	data->img = mlx_new_image(data->mlx, W_IMG, H_IMG);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	init_info(t_info *info)
{
	info->vec_onscrn = vec3(0.0, 0.0, 0.0);
	info->vec_view = vec3(0.0, 0.0, -5.0);
	info->vec_light = vec3(-5.0, 5.0, -5.0);
	info->vec_ray = vec3(0.0, 0.0, 0.0);
	info->vec_ctr = vec3(0.0, 0.0, 5.0);
	info->vec_ctr_to_view = sub(&(info->vec_view), &(info->vec_ctr));
	info->radius = 1.0;
	info->buf = squared_norm(&(info->vec_ctr_to_view)) - SQR(info->radius);
}

int	main(void)
{
	t_data	data;
	t_info	info;
	double	x_img;
	double	y_img;

	init_data(&data);
	init_info(&info);
	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			my_mlx_pixel_put(&data,(int)x_img, (int)y_img, raytrace(x_img, y_img, &info));
			x_img++;
		}
		y_img++;
	}
	mlx_hook(data.mlx_win, 33, 1 << 17, ft_exit, &data);
	mlx_key_hook(data.mlx_win, key_hook, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
