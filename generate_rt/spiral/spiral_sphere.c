#include <math.h>
#include <stdio.h>
#include "miniRT.h"

typedef struct s_putsph
{
	t_vec3	start;
	t_vec3	direct;
	double	diameter;
	double	add_vector;
	double	add_degrees;
	double	gap;
	int		cnt;
}	t_putsph;

void	spiral_sphere(t_putsph *p)
{
	//dx, dy
	normalize(&p->direct);
	t_vec3	vec_ey = vec3(0, 1, 0);
	t_vec3	vec_dx = cross(vec_ey, p->direct);
	normalize(&vec_dx);
	t_vec3	vec_dy = cross(p->direct, vec_dx);
	normalize(&vec_dy);

	t_vec3	point;
	double	t = 1;
	double	deg = 0;
	double	radi = radians(deg);
	int		r;
	int		g;
	int		b;
	int		cnt = p->cnt;

	while (cnt--)
	{
		point = add(p->start, \
				add(times(t, p->direct), \
				add(times(p->gap * cos(radi), vec_dx), \
					times(p->gap * sin(radi), vec_dy))));
		r = ((cnt % 2 == 0)? 0 : 255);
		g = ((cnt % 3 == 0)? 0 : 255);
		b = ((r == 255 && g == 255)? 0 : 255);
		printf("sp %f,%f,%f %f %d,%d,%d\n", point.x, point.y, point.z, p->diameter, r, g, b);
		t += p->add_vector;
		deg += p->add_degrees;
		radi = radians(deg);
	}
}
int main(void)
{
	t_putsph p;
	p.start = vec3(-30, 100, 30);
	p.direct = vec3(1, -1, -1);
	p.diameter = 10;
	p.add_vector = 2;
	p.add_degrees = 10;
	p.gap = 30;
	p.cnt = 100;
	spiral_sphere(&p);
}