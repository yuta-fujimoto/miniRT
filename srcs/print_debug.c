#include "miniRT.h"

char	*vector_str(const t_vec3 v)
{
	static char	buf[1024];

	memset(buf, 0, sizeof(buf));
	sprintf((void *)buf, "(%f, %f, %f)", v.x, v.y, v.z);
	return (buf);
}

void	print_color(t_color c, char *prefix)
{
	printf("%s: %f %f %f\n", prefix, c.r, c.g, c.b);
}

void	print_vec3(t_vec3 v, char *prefix)
{
	printf("%s: %f %f %f\n", prefix, v.x, v.y, v.z);
}

void	print_obj(t_list *l)
{
	while (l)
	{
		if (l->cont_type == Sphere)
		{
			printf("[SPHERE]\n");
			print_vec3(((t_sphere *)l->content)->center, "CENTER");
			printf("DIAM: %le\n", ((t_sphere *)l->content)->diameter);
			print_color(((t_sphere *)l->content)->c, "COLOR");
		}
		else if (l->cont_type == Plane)
		{
			printf("[PLANE]\n");
			print_vec3(((t_plane *)l->content)->pos, "POSITION");
			print_vec3(((t_plane *)l->content)->norm_ori_vec, "NORM VEC");
			print_color(((t_plane *)l->content)->c, "COLOR");
		}
		else if (l->cont_type == Cylinder)
		{
			printf("[CYLINDER]\n");
			print_vec3(((t_cylinder *)l->content)->pos, "POSITION");
			print_vec3(((t_cylinder *)l->content)->norm_ori_vec, "NORM VEC");
			printf("DIAM, HEIGHT: %le %le\n", ((t_cylinder *)l->content)->diameter, ((t_cylinder *)l->content)->height);
			print_color(((t_cylinder *)l->content)->c, "COLOR");
		}
		else
		{
			printf("WARNING: UNEXPECTED CONTENT TYPE\n");
		}
		l = l->next;
	}
}

void	print_world(t_world *w)
{
	printf("[AMBIENT]\n");
	printf("RATIO: %le\n", w->amb_light.ratio);
	print_color(w->amb_light.c, "COLOR");
	printf("[CAMERA]\n");
	print_vec3(w->camera.pos, "POSITION");
	print_vec3(w->camera.norm_ori_vec, "NORM VEC");
	printf("FOV: %d\n", w->camera.fov);
	printf("[LIGHT]\n");
	print_vec3(w->light.pos, "POSITION");
	printf("RATIO: %le\n", w->light.ratio);
	print_obj(w->obj_list);
}
