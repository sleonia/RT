#include "rtv1.h"

int 		color_scale(int	color, double c)
{
	int 	red;
	int 	green;
	int 	blue;

	red = (color & 0xFF0000) >> 16;
	red = (int)((double)red * c);
	green = (color & 0x00FF00) >> 8;
	green = (int)((double)green * c);
	blue = (color & 0x0000FF);
	blue = (int)((double)blue * c);
	return ((red << 16) | (green << 8) | blue);
}

t_result	intersect_ray_sphere(t_pos *o, t_pos *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;
	t_result	res;

	oc = vector_minus(o, sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(&oc, d);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
//	printf ("%f %f\n", res->t1, res->t2);
	return (res);
}


t_return	closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_sphere *sphere)
{
	t_result	res;
	t_sphere	*tmp;
	t_return	ret;

	ret.closest_t = INFINITY;
	ret.closest_sphere = NULL;
	tmp = sphere;
	while (tmp)
	{
		res = intersect_ray_sphere(o, d, tmp);
		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_sphere = tmp;
		}
		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_sphere = tmp;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_pos		reflect_ray(t_pos *r, t_pos *n)
{
	t_pos	ret;
	t_pos	a;
	t_pos	b;

	a = vector_on_number(n, 2);
	b = vector_on_number(&a, dot(r, n));
	ret = vector_minus(&b, r);
	return (ret);
}

/*
** 		Находит ближайшую точку в позиции (x, y) среди всех сфер и возвращает цвет пикселя
*/
int			 trace_ray(t_pos *o, t_pos *d, double t_min, double t_max, t_scene *scene, int depth) {
	t_pos p;
	t_pos n;
	t_pos buf;
	t_pos r;
	t_return ret;
	double c;
	int local_color;
	int reflected_color;
	double ref;

	ret = closest_intersection(o, d, t_min, t_max, scene->figure->sphere);
	if (ret.closest_sphere == NULL)
		return (BLACK);
//	return (ret.closest_sphere->color);
	//Часть для добавления бликов от света
	// 		Вычисление локального цвета
	buf = vector_on_number(d, ret.closest_t);
	p = vector_pus(o, &buf);
	n = vector_minus(&p, ret.closest_sphere->center);
	n = vector_div(&n, vector_len(&n));
	//Теперь buf это -D
	buf = vector_on_number(d, -1);
	// Вычисление коэфа для умножения на цвет сферы
	c = computer_lighting(&p, &n, &buf, ret.closest_sphere->specular, scene);
	local_color = color_scale(ret.closest_sphere->color, c);

	// Проверка выхода из рекурсии
	ref = ret.closest_sphere->reflective;
	if (depth <= 0 || ref <= 0 || scene->off->reflect)
		return (local_color);

	//Рекурсивная часть отражения объектов
	r = reflect_ray(&buf, &n);
	reflected_color = trace_ray(&p, &r, 0.001, INFINITY, scene, depth - 1);
	return (color_scale(local_color, 1 - ref) + color_scale(reflected_color, ref));
}
