#include <math.h>
#include <stdio.h>
#include "miniRT.h"

typedef struct s_spiral
{
	t_vec3	start_centerline;
	t_vec3	direct_centerline;
	double	diameter_sphere;
	double	increment_centerline;
	double	increment_degree;
	double	gap_sphere_centerline;
	int		num_sphere;
}	t_spiral;

void	put(t_spiral *setting)
{
	// dx, dy
	normalize(&setting->direct_centerline);
	t_vec3	vec_ey = vec3(0, 1, 0);
	t_vec3	vec_dx = cross(vec_ey, setting->direct_centerline);
	normalize(&vec_dx);
	t_vec3	vec_dy = cross(setting->direct_centerline, vec_dx);
	normalize(&vec_dy);

	t_vec3	point;
	double	t = 1;
	double	degree = 0;
	double	radi = radians(degree);
	int		cnt = setting->num_sphere;
	int		r;
	int		g;
	int		b;
	char	*mode;

	while (cnt--)
	{
		point = add(setting->start_centerline, \
				add(times(t, setting->direct_centerline), \
				add(times(setting->gap_sphere_centerline * cos(radi), vec_dx), \
					times(setting->gap_sphere_centerline * sin(radi), vec_dy))));
		// color
		r = ((cnt % 2 == 0)? 0 : 255);
		g = ((cnt % 3 == 0)? 0 : 255);
		b = ((r == 255 && g == 255)? 0 : 255);
		mode = ((cnt % 2 == 0)? "PERFECT" : "SPECULAR");
		printf("sp %f,%f,%f %f %d,%d,%d %s\n", point.x, point.y, point.z, setting->diameter_sphere, r, g, b, mode);
		t += setting->increment_centerline;
		degree += setting->increment_degree;
		radi = radians(degree);
	}
}

int main(void)
{
	t_spiral setting;
	setting.start_centerline = vec3(-30, 100, 30);
	setting.direct_centerline = vec3(1, -1, -1);
	setting.diameter_sphere = 10;
	setting.increment_centerline = 2;
	setting.increment_degree = 20;
	setting.gap_sphere_centerline = 30;
	setting.num_sphere = 100;
	put(&setting);
}
