#include "tutorial.h"

void put_info(t_info *info)
{
	//norminette
	printf("------------------------>info\n");
	printf("vec->onscrn->%s\n", vector_str(&(info->pos_onscrn)));
	printf("pos_camera->%s\n", vector_str(&(info->pos_camera)));
	printf("pos_light->%s\n", vector_str(&(info->pos_light)));
	printf("dir_ray->%s\n", vector_str(&(info->dir_ray)));
	printf("vec_ctr->%s\n", vector_str(&(info->vec_ctr)));
	printf("vec_ctr_to_view->%s\n", vector_str(&(info->vec_ctr_to_view)));
	printf("vec_int->%s\n", vector_str(&(info->vec_int)));
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	get_brilliance(t_info *info, double dot_norm_inc)
{
	double	br_env;
	double	br_diffuse;
	double	br_mirror;
	t_vec3	vec_ref;
	t_vec3	pos_camera_reverse;

	br_env = REF_FACTOR_ENV * ILLUMI_RATE_ENV;
	if (dot_norm_inc > 0)
	{
		br_diffuse = REF_FACTOR_DIFFUSE * ILLUMI_RATE_DIR * dot_norm_inc;
		vec_ref = sub_deep(times(2*dot_norm_inc, &(info->vec_norm)), info->vec_inc);
		normalize(&vec_ref);
		pos_camera_reverse = times(-1, &(info->dir_ray));
		//normalize(&pos_camera_reverse);
		br_mirror = REF_FACTOR_MIRROR * ILLUMI_RATE_DIR * pow(dot(&vec_ref, &pos_camera_reverse), GLOSSINESS);
	}
	else
	{
		br_diffuse = 0;
		br_mirror = 0;
	}
	return(br_env + br_diffuse + br_mirror);
}

color_int	reflection(t_info *info, double t)
{
	int		rgb;
	double	brilliance;

	info->vec_int = add_deep(info->pos_camera, times(t, &(info->dir_ray)));
	info->vec_inc = sub(&(info->pos_light), &(info->vec_int));
	normalize(&(info->vec_inc));
	info->vec_norm = sub(&(info->vec_int), &(info->vec_ctr));
	normalize(&(info->vec_norm));
	brilliance = get_brilliance(info, dot(&(info->vec_norm), &(info->vec_inc)));
	if (brilliance > 1)
		brilliance = 1;
	rgb = 255 * brilliance;
	return (create_trgb(0, rgb, rgb, rgb));
}

t_vec3	conv2to3(double x_img, double y_img)
{
	t_vec3	pos_onscrn;
	double	w_scrn = 2;
	double	h_scrn = 2;

	pos_onscrn.x = w_scrn * (x_img / (W_IMG - 1)) - (w_scrn / 2);
	pos_onscrn.y = h_scrn * (y_img / (H_IMG - 1)) - (h_scrn / 2);
	pos_onscrn.z = 0;
	return (pos_onscrn);
}

double	get_t(double a, double b, double d)
{
	double	d_sqrt;
	double	mol1;
	double	mol2;

	if (d >= 0)
	{
		d_sqrt = sqrt(d);
		mol1 = -b + d_sqrt;
		mol2 = -b - d_sqrt;
		if (0 < mol1 && mol1 < mol2)//計算後を比較
			return (mol1 / 2 * a);
		else if (0 < mol2)
			return (mol2 / 2 * a);
	}
	return (-1);
}

typedef enum e_formula
{
	A,
	B,
	C,
	D,
	FORMULA_NUM
}	t_formula;

color_int	raytrace(double x_img, double y_img, t_info *info)
{
	double	form[FORMULA_NUM];
	double	t;

	info->pos_onscrn = conv2to3(x_img, y_img);
	info->dir_ray = (sub(&(info->pos_onscrn), &(info->pos_camera)));
	normalize(&(info->dir_ray));
	form[A] = squared_norm(&(info->dir_ray));
	form[B] = 2 * dot(&(info->vec_ctr_to_view), &(info->dir_ray));
	form[C] = info->buf;
	form[D] = SQR(form[B]) - 4 * form[A] * form[C];
	t = get_t(form[A], form[B], form[D]);
	if (t > 0)
		return (reflection(info, t));
	return (PURPLE);
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, W_IMG, H_IMG, "fyuta & rakiyama in the house");
	data->img = mlx_new_image(data->mlx, W_IMG, H_IMG);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	init_info(t_info *info)
{
	info->pos_onscrn = vec3(0.0, 0.0, 0.0);
	info->pos_camera = vec3(0.0, 0.0, -5.0);
	info->pos_light = vec3(-5.0, 5.0, -5.0);
	info->dir_ray = vec3(0.0, 0.0, 0.0);
	info->vec_ctr = vec3(0.0, 0.0, 5.0);
	info->vec_ctr_to_view = sub(&(info->pos_camera), &(info->vec_ctr));
	info->vec_int = vec3(0.0, 0.0, 0.0);
	info->vec_inc = vec3(0.0, 0.0, 0.0);
	info->vec_norm = vec3(0.0, 0.0, 0.0);
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
