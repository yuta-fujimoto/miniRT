#include "mlx.h"
#include "vector_utils.h"
#include <stdio.h>
#include <stdbool.h>

//color
#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define WHITE 0x00FFFFFF

#define W_IMG 500
#define H_IMG 500

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void sub(vector_t* o, const vector_t*a, const vector_t*b)
{
	o->x = a->x - b->x;
	o->y = a->y - b->y;
	o->z = a->z - b->z;
}

//want to generalize
void conv2to3(vector_t *vec_onscrn, double x_img, double y_img)
{
	double	w_scrn = 2;
	double	h_scrn = 2;

	vec_onscrn->x = w_scrn * (x_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn->y = h_scrn * (y_img / (W_IMG - 1)) - (w_scrn / 2);
	vec_onscrn->z = 0;
}

bool is_crossed(double x_img, double y_img)
{
    vector_t	vec_onscrn;
	conv2to3(&vec_onscrn, x_img, y_img);
	vector_t	vec_view = {0.0f, 0.0f, -5.0f};
	vector_t	vec_ray;
	sub(&vec_ray, &vec_onscrn, &vec_view);
	vector_t	vec_ctr = {0.0f, 0.0f, 5.0f};
	vector_t	vec_ctr_to_view;
	sub(&vec_ctr_to_view, &vec_view, &vec_ctr);
	double		radius = 1.0;
	double		A = squared_norm(&vec_ray);
	double		B = 2 * dot(&vec_ctr_to_view, &vec_ray);
	double		C = squared_norm(&vec_ctr_to_view) - (radius * radius);
	double		D = B * B - 4 * A * C;
	if (D >= 0)
		return (true);
	else
		return (false);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	data;
	double	x_img;
	double	y_img;
	int		color;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W_IMG, H_IMG, "Tuttoluu");
	data.img = mlx_new_image(mlx, W_IMG, H_IMG);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	y_img = 0;
	while (y_img < H_IMG)
	{
		x_img = 0;
		while (x_img < W_IMG)
		{
			if (is_crossed(x_img, y_img))
				color = GREEN;
			else
				color = BLACK;
			my_mlx_pixel_put(&data,(int)x_img, (int)y_img, color);
			x_img++;
		}
		y_img++;
	}
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	mlx_loop(mlx);
}
