#include "miniRT.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color dcolor)
{
	char	*dst;
	int		icolor;

	icolor = (((int)dcolor.r * 255) << 16) | (((int)dcolor.g * 255) << 8) | (int)dcolor.b * 255; 
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = icolor;
}

t_vec3 pos_onscrn(double x_img, double y_img, const t_camera *cam)
{
	const t_vec3	vec_ey = vec3(0, 1, 0);
	const double	coef_n = W_SCRN / (2 * tan(RADIANS((double)cam->fov / 2)));
	t_vec3			vec_dx;
	t_vec3			vec_dy;
	double			coef_dx;
	double			coef_dy;

	vec_dx = cross(vec_ey, cam->norm_ori_vec);
	vec_dy = cross(cam->norm_ori_vec, vec_dx);
	coef_dx = (W_SCRN * (x_img / (W_IMG - 1))) - (W_SCRN / 2);
	coef_dy = (-H_SCRN * (y_img / (H_IMG - 1))) + (H_SCRN / 2);
	return (add(cam->pos, add(times(coef_n, cam->norm_ori_vec), add(times(coef_dx, vec_dx), times(coef_dy, vec_dy)))));
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
			camray.direction = sub(pos_onscrn(x_img, y_img, &(w.camera)), camray.start);
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
