#include "miniRT.h"
#include <pthread.h>

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

t_vec3	to3axis(const double x_img, \
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

void	default_set(const t_world *w, t_default *def)
{
	def->cam = w->camera;
	def->vec_ey = vec3(0, 1, 0);
	def->vec_dx = cross(def->vec_ey, def->cam.norm_ori_vec);
	if (def->vec_dx.x == 0.0 && def->vec_dx.y == 0.0 && def->vec_dx.z == 0.0)
	{
		def->vec_ey = vec3(0, 1, 0.01);
		def->vec_dx = cross(def->vec_ey, def->cam.norm_ori_vec);
	}
	normalize(&def->vec_dx);
	def->vec_dy = cross(def->cam.norm_ori_vec, def->vec_dx);
	normalize(&def->vec_dy);
	def->coef_n = W_SCRN / (2 * tan(radians((double)def->cam.fov / 2)));
	def->max_xi = W_IMG - 1;
	def->max_yi = H_IMG - 1;
	def->h_scrn = H_IMG * W_SCRN / W_IMG;
	def->half_ws = W_SCRN / 2;
	def->half_hs = def->h_scrn / 2;
}

void *draw(void *p)
{
	t_color		col;
	t_block		*block;
	double		x_img;
	double		y_img;

	block = (t_block *)p;
	y_img = block->start_y;
	while (y_img - block->start_y < block->data->y_stride && y_img < H_IMG)
	{
		x_img = block->start_x;
		while (x_img - block->start_x < block->data->x_stride && x_img < W_IMG)
		{
			block->camray.direction = to3axis(x_img, y_img, &block->data->def);
			if (!raytrace(&block->data->w, &block->camray, &col))
				col = color(1.0, 1.0, 1.0);
			my_mlx_pixel_put(block->data, (int)x_img, (int)y_img, col);
			x_img++;
		}
		y_img++;
	}
	return (NULL);
}

void	data_set(t_data *data)
{
	pthread_t	th[W_BLOCK][H_BLOCK];
	t_block		blocks[W_BLOCK][H_BLOCK];
	int			x_i;
	int			y_i;

	data->x_stride = ceil(W_IMG / W_BLOCK) + 1;
	data->y_stride = ceil(H_IMG / H_BLOCK) + 1;
	default_set(&data->w, &data->def);
	y_i = 0;
	while (y_i < H_BLOCK)
	{
		x_i = 0;
		while (x_i < W_BLOCK)
		{
			blocks[x_i][y_i].data = data;
			blocks[x_i][y_i].start_x = x_i * data->x_stride;
			blocks[x_i][y_i].start_y = y_i * data->y_stride;
			blocks[x_i][y_i].camray.start = data->w.camera.pos;
			if (pthread_create(&th[x_i][y_i], NULL, draw, &blocks[x_i][y_i]))
				printf("ERROR!!");
			x_i++;
		}
		y_i++;
	}
	y_i = 0;
	while (y_i < H_BLOCK)
	{
		x_i = 0;
		while (x_i < W_BLOCK)
		{
			if (pthread_join(th[x_i][y_i], NULL))
				printf("ERROR!!");
			x_i++;
		}
		y_i++;
	}
}

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
