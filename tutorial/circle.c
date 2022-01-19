#include "tutorial.h"

const char* vector_str(const t_vec3*v)
{
	//will be deleted
	static char buf[1024];
	memset(buf, 0, sizeof(buf));
	sprintf((void*)buf, "(%f, %f, %f)", v->x, v->y, v->z);
	return buf;
}

void put_info(t_info *info)
{
	//will be deleted
	printf("------------------------>info\n");
	printf("vec->onscrn->%s\n", vector_str(&(info->pos_onscrn)));
	printf("pos_camera->%s\n", vector_str(&(info->pos_camera)));
	printf("pos_light->%s\n", vector_str(&(info->pos_light)));
	printf("camera_to_onscrn->%s\n", vector_str(&(info->camera_to_onscrn)));
	printf("pos_centr->%s\n", vector_str(&(info->pos_centr)));
	printf("centr_to_camera->%s\n", vector_str(&(info->centr_to_camera)));
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

double	get_brilliance(t_info *info, double vertical_dot_incident)
{
	double	br_env;
	double	br_diffuse;
	double	br_mirror;
	t_vec3	vec_reflection;
	t_vec3	inverse_camera_to_onscrn;

	br_env = REF_FACTOR_ENV * ILLUMI_RATE_ENV;
	if (vertical_dot_incident > 0)
	{
		br_diffuse = REF_FACTOR_DIFFUSE * ILLUMI_RATE_DIR * vertical_dot_incident;
		vec_reflection = sub(times(2*vertical_dot_incident, info->pos_vertical), info->pos_incident);
		normalize(&vec_reflection);
		inverse_camera_to_onscrn = times(-1, info->camera_to_onscrn);
		//normalize(&inverse_camera_to_onscrn);
		br_mirror = REF_FACTOR_MIRROR * ILLUMI_RATE_DIR * pow(dot(&vec_reflection, &inverse_camera_to_onscrn), GLOSSINESS);
	}
	else
	{
		br_diffuse = 0;
		br_mirror = 0;
	}
	return(br_env + br_diffuse + br_mirror);
}

color_int	get_color(t_info *info, double t)
{
	t_vec3	pos_intersection;
	int		rgb;
	double	brilliance;

	pos_intersection = add(info->pos_camera, times(t, info->camera_to_onscrn));
	info->pos_incident = sub(info->pos_light, pos_intersection);
	normalize(&(info->pos_incident));
	info->pos_vertical = sub(pos_intersection, info->pos_centr);
	normalize(&(info->pos_vertical));
	brilliance = get_brilliance(info, dot(&(info->pos_vertical), &(info->pos_incident)));
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
	double	t1;
	double	t2;

	if (d >= 0)
	{
		d_sqrt = sqrt(d);
		t1 = (-b + d_sqrt) / 2 * a;
		t2 = (-b - d_sqrt) / 2 * a;
		if (0 < t1 && (t1 < t2 || t2 <= 0))
			return (t1);
		else if (0 < t2)
			return (t2);
	}
	return (0);
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
	info->camera_to_onscrn = sub(info->pos_onscrn, info->pos_camera);
	normalize(&(info->camera_to_onscrn));
	form[A] = squared_norm(&(info->camera_to_onscrn));
	form[B] = 2 * dot(&(info->centr_to_camera), &(info->camera_to_onscrn));
	form[C] = info->buf;
	form[D] = SQR(form[B]) - 4 * form[A] * form[C];
	t = get_t(form[A], form[B], form[D]);
	if (t > 0)
		return (get_color(info, t));
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
	info->pos_onscrn = vec3(0, 0, 0);
	info->pos_camera = vec3(0, 0, -5.0);
	info->pos_light = vec3(-5.0, 5.0, -5.0);
	info->camera_to_onscrn = vec3(0, 0, 0);
	info->pos_centr = vec3(0, 0, 5.0);
	info->centr_to_camera = sub(info->pos_camera, info->pos_centr);
	info->pos_incident = vec3(0, 0, 0);
	info->pos_vertical = vec3(0, 0, 0);
	info->radius = 1.0;
	info->buf = squared_norm(&(info->centr_to_camera)) - SQR(info->radius);
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
