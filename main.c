#include "rtv1.h"
#include <math.h>

/*
** Решает квадратное уравнение и возвращает два корня если есть, если нет то INF
*/

t_result	*IntersectRaySphere(t_result *res, t_cam *o, t_view *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;


	oc = vector_minus(o->position, sphere->center);
	k1 = dot(d->position, d->position);
	k2 = 2 * dot(&oc, d->position);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res->t1 = INFINITY;
		res->t2 = INFINITY;
		return (res);
	}
	res->t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res->t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
//	printf ("%f %f\n", res->t1, res->t2);
	return (res);
}

/*
** Находит ближайшую точку в позиции (x, y) среди всех сфер и закрашивает цветом
*/

int			TraceRay(t_cam *o, t_view *d, double t_min, double t_max, t_sphere *sphere)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_result	*res;
	t_sphere	*tmp;

	closest_t = INFINITY;
	closest_sphere = NULL;
	res = (t_result *)ft_memalloc(sizeof(t_result));
	tmp = sphere;
	while (tmp)
	{
		res = IntersectRaySphere(res, o, d, tmp);
//		printf ("%f %f\n", res->t1, res->t2);
		if (res->t1 >= t_min && res->t1 <= t_max && res->t1 < closest_t)
		{
			closest_t = res->t1;
			closest_sphere = tmp;
		}
		else if (res->t2 >= t_min && res->t2 <= t_max && res->t2 < closest_t)
		{
			closest_t = res->t2;
			closest_sphere = tmp;
		}
		tmp = tmp->next;
	}
//	printf ("%f %f\n", res->t1, res->t2);
	free(res);
	if (closest_sphere == NULL)
		return (WHITE);
	return (closest_sphere->color);
}

int 		*put_pixel(double x, double y, int color, t_sdl *sdl)
{
	int		xnew;
	int		ynew;

	xnew = WIDTH / 2 + (int)x;
	ynew = HEIGHT / 2 - (int)y;
//	printf("%d \n", (int)xnew + (int)ynew * WIDTH);
	sdl->pixels[xnew + ynew * WIDTH] = color;
	return (sdl->pixels);
}

/*
** Заменить на парсер
*/

t_sphere	*init_sphere(t_sphere *sphere)
{
	t_sphere	*tmp;
	t_pos		*center1;
	t_pos		*center2;
	t_pos		*center3;

	sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center1 = (t_pos *)ft_memalloc(sizeof(t_pos));
	sphere->radius  = 1;
	sphere->color = 0xFF0000;
	sphere->center = insert(0, -1, 3, center1);

	sphere->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center2 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = sphere->next;
	tmp->radius  = 1;
	tmp->color = 0x0000FF;
	tmp->center = insert(2, 0, 4, center2);

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	center3 = (t_pos *)ft_memalloc(sizeof(t_pos));
	tmp = tmp->next;
	tmp->radius  = 1;
	tmp->color = 0x00FF00;
	tmp->center = insert(-2, 0, 4, center3);
	return (sphere);
}

int			main(void)
{
	t_cam		*o;
	t_view		*d;
	t_sphere	*sphere;
	int			x;
	int			y;
	int 		color;
	t_sdl		*sdl;


	sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(sdl);

	//парсер чтобы считать сферы из файла в *shpere
	o = (t_cam *)ft_memalloc(sizeof(t_cam));
	o->position = (t_pos *)ft_memalloc(sizeof(t_pos));
	d = (t_view *)ft_memalloc(sizeof(t_view));
	d->position = (t_pos *)ft_memalloc(sizeof(t_pos));
//	d->position = (t_pos *)ft_memalloc(sizeof(t_pos));

	o->position = insert(0, 0, 0, o->position);
	x = -WIDTH / 2;
	sphere = NULL;
	sphere = init_sphere(sphere);
	while(x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while(y < HEIGHT / 2)
		{
			d->position = canvas_to_viewport(x, y, d->position);
//			printf("%f %f %f\n", d->position->x, d->position->y, d->position->z);
			color = TraceRay(o, d, 1.0, INFINITY, sphere);
			sdl->pixels = put_pixel(x, y, color, sdl);
			y++;
		}
		x++;
	}
	sdl_control(sdl);
	return (0);
}