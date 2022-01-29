#include <math.h>
#include <stdio.h>
#include "srcs/miniRT.h"

# define RADIANZERO 1
# define YZERO 200
# define CENTER_RADIUS 50
# define CMAX 255

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

//enum e_rgb
//{
//	R,
//	G,
//	B,
//	COLOR_NUM
//};

//void	put_shpere()
//{
//	double			x;
//	static double	y = YZERO;
//	double			z;
//	double			diameter = 10;
//	int				color[COLOR_NUM];
//	static double	radians = RADIANZERO;
//	static unsigned int	c = 1;

//	x = CENTER_RADIUS * cos(radians);
//	z = CENTER_RADIUS * sin(radians);
//	color[R] = ((c % 2 == 0)? 0 : 255);
//	color[G] = ((c % 3 == 0)? 0 : 255);
//	color[B] = ((color[R] == 255 && color[G] == 255)? 0 : 255);
//	printf("sp %f,%f,%f %f %d,%d,%d\n", x, y, z, diameter, color[R], color[G], color[B]);
//	y -= 2;
//	radians += 0.2;
//	c ++;
//}

void	spiral_sphere(t_putsph *p)
{
	//dx, dy
	normalize(&p->direct);
	t_vec3	vec_ey = vec3(1, 0, 0);
	//t_vec3	vec_ey = vec3(0, 1, 0);
	t_vec3	vec_dx = cross(vec_ey, p->direct);
	normalize(&vec_dx);
	//printf("%s\n", vector_str(vec_dx));
	//exit(1);
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
	printf("A 0.2 255,255,255\n");
	printf("L -100,100,30 0.7 255,255,255\n");
	printf("C -100,50,0 1,0,0 70\n");
	printf("\n");
	printf("pl 0,0,0 0,1,0 0,255,225\n");
	printf("pl 0,0,300 -0.2,0,-0.5 0,255,225\n");
	printf("pl 0,0,-300 0.2,0,0.5 0,255,225\n");
	printf("cy 0,0,0 0,1,0 20 220 10,0,255\n");
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