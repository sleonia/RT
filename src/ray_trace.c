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

	oc = vector_minus(o, &sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(&oc, d);
	k3 = dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0.001)
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

/*int     	get_intersect_cylinder(const t_vector3d start_ray, const t_vector3d ray, const t_object3d obj,
								  float *intersect_dist, const float min_distance)
{
	float       intersect_check, intersect_tmp;
	float       a, b, c;
	float       discriminant;
	t_vector3d  OC;

	intersect_tmp = *intersect_dist;
	OC = mv_minus(start_ray, obj.center);
	a = 1 - mv_scalar_mult(ray, obj.axis) * mv_scalar_mult(ray, obj.axis);

	b = mv_scalar_mult(ray, OC) - mv_scalar_mult(ray, obj.axis) * mv_scalar_mult(OC, obj.axis);

	c = mv_scalar_mult(OC, OC) - mv_scalar_mult(OC, obj.axis) *
								 mv_scalar_mult(OC, obj.axis) - obj.sq_radius;
	discriminant = b * b - a * c;
	if (discriminant < 0.001)
		return (0);
	intersect_check = (-b - sqrt(discriminant)) / a;
	if (intersect_check < *intersect_dist && intersect_check > min_distance)
		*intersect_dist = intersect_check;
	if (*intersect_dist == intersect_tmp)
		return (0);
	return (1);
}*/

t_result	intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cylinder)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_pos		oc;
	t_result	res;

	oc = vector_minus(o, &cylinder->center);
	a = 1.0 - dot(d, &cylinder->axis) * dot(d, &cylinder->axis);
	b = dot(d, &oc) - dot(d, &cylinder->axis) * dot(&oc, &cylinder->axis);
	c = dot(&oc, &oc) - dot(&oc, &cylinder->axis) * dot(&oc, &cylinder->axis) - cylinder->radius * cylinder->radius;
	discriminant = b * b - a * c;
	if (discriminant < 0.001)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-b - sqrt(discriminant)) / a;
	res.t2 = INFINITY;
	return (res);
}

t_result	get_intersect(t_pos *o, t_pos *d, t_object *obj)
{
	if (obj->type == o_sphere)
		return (intersect_ray_sphere(o, d, &obj->objects->sphere));
	else if (obj->type == o_cylinder)
		return (intersect_ray_cylinder(o, d, &obj->objects->cylinder));
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

t_pos	get_obj_normal(t_pos *p, t_object *obj)
{
	t_pos n;

	if (obj->type == o_sphere)
		n = vector_minus(p, &obj->objects->sphere.center);
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
	n = get_obj_normal(&p, ret.closest_obj);
	//Теперь buf это -D
	buf = vector_on_number(d, -1);
	// Вычисление коэфа для умножения на цвет сферы
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
