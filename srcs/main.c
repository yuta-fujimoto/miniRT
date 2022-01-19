#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color dcolor)
{
	char	*dst;
	int		color;

	color = (((int)dcolor.r * 255) << 16) + (((int)dcolor.g * 255) << 8) + (int)dcolor.b * 255; 
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

int main(int ac, char **av)
{
	t_world	w;
	t_ray	camray;
	t_data	data;
	double x_img;
	double y_img;
	t_color col;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W_IMG, H_IMG, "Defence Line");
	data.img = mlx_new_image(data.mlx, W_IMG, H_IMG);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	if (ac != 2)
	{
		ft_putendl_fd("NO ARGUMENT", STDERR_FILENO);
		return (0);
	}
	if (!parser(av[1], &w))
	{
		ft_putendl_fd("ERROR", STDERR_FILENO);
		return (0);
	}
	print_world(&w);
	camray.start = w.camera.pos;
	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			camray.direction = sub(conv2to3(x_img, y_img), camray.start);
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
	end_world(&w, true);
}
