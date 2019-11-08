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



t_return	closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_object *obj)
{
	t_result	res;
	t_object	*tmp_obj;
	t_return	ret;

	ret.closest_t = INFINITY;
	ret.closest_obj = NULL;
	tmp_obj = obj;
	while (tmp_obj)
	{
		res = get_intersect(o, d, tmp_obj);
		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_obj = tmp_obj;
		}
		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_obj = tmp_obj;
		}
		tmp_obj = tmp_obj->next;
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

t_pos	get_cone_normal(t_pos *start_ray, t_pos *ray, t_cone *obj,
									 double intersect_dist)
{
	t_pos	retNormal;
	t_pos	oc = vector_minus(start_ray, &obj->center);

	double	card = dot(ray, &obj->axis);
	double	caoc = dot(&oc, &obj->axis);
	double	k2 = obj->radius * obj->radius;
	double	m = card * intersect_dist + caoc;
	t_pos mult = vector_on_number(ray, intersect_dist);
	t_pos vec_plus = vector_pus(&mult, &oc);
	t_pos v = vector_on_number(&obj->axis, (1 + k2) * m);
	retNormal = vector_minus(&vec_plus, &v);

	return (retNormal);
}

t_pos get_cylinder_normal(t_pos *start_ray, t_pos *ray, t_cylinder *obj, double intersect_dist, t_pos *intersect_point)
{
	t_pos n;

	t_pos v = vector_minus(intersect_point, &obj->center);
	n = vector_on_number(&obj->axis, dot(&v, &obj->axis));
	n = vector_minus(&v, &n);

	return (n);
}

t_pos	get_obj_normal(t_pos *p, t_object *obj, double intersect_dist, t_pos *o, t_pos *d)
{
	t_pos n;

	if (obj->type == o_sphere)
		n = vector_minus(p, &obj->objects->sphere.center);
	else if (obj->type == o_plane)
		n = obj->objects->plane.normal;
	else if (obj->type == o_cone)
		n = get_cone_normal(o, d, &obj->objects->cone, intersect_dist);
	else if (obj->type == o_cylinder)
		n = get_cylinder_normal(o, d, &obj->objects->cylinder, intersect_dist, p);
	n = vector_div(&n, vector_len(&n));
	return (n);
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

	ret = closest_intersection(o, d, t_min, t_max, scene->object);
	if (ret.closest_obj == NULL)
		return (BLACK);
	buf = vector_on_number(d, ret.closest_t);
	p = vector_pus(o, &buf);
	n = get_obj_normal(&p, ret.closest_obj, ret.closest_t, o, d);
	//Теперь buf это -D
	buf = vector_on_number(d, -1);
//	// Вычисление коэфа для умножения на цвет сферы
	c = computer_lighting(&p, &n, &buf, ret.closest_obj->specular, scene);
	local_color = color_scale(ret.closest_obj->color, c);

	// Проверка выхода из рекурсии
	ref = ret.closest_obj->reflective;
	if (depth <= 0 || ref <= 0 || scene->off->reflect)
		return (local_color);

	//Рекурсивная часть отражения объектов
	r = reflect_ray(&buf, &n);
	reflected_color = trace_ray(&p, &r, 0.001, INFINITY, scene, depth - 1);
	return (color_scale(local_color, 1 - ref) + color_scale(reflected_color, ref));
}
