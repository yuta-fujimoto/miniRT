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
