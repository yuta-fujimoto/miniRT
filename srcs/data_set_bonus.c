#include "miniRT.h"
#include <pthread.h>

static void	*draw(void *p)
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

static void	wait_draw(t_data *data, pthread_t th[W_BLOCK][H_BLOCK])
{
	int	x_i;
	int	y_i;

	y_i = 0;
	while (y_i < H_BLOCK)
	{
		x_i = 0;
		while (x_i < W_BLOCK)
		{
			if (pthread_join(th[x_i][y_i], NULL))
				ft_exit(data, EXIT_FAILURE);
			x_i++;
		}
		y_i++;
	}
}

void	data_set(t_data *data)
{
	pthread_t	th[W_BLOCK][H_BLOCK];
	t_block		blocks[W_BLOCK][H_BLOCK];
	int			x_i;
	int			y_i;

	data->x_stride = ceil(W_IMG / W_BLOCK);
	data->y_stride = ceil(H_IMG / H_BLOCK);
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
				ft_exit(data, EXIT_FAILURE);
			x_i++;
		}
		y_i++;
	}
	wait_draw(data, th);
}
