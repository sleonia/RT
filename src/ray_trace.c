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

t_result	intersect_ray_cone(t_pos * o, t_pos *d, t_cone *cone)
{
	t_pos	x = vector_minus(o, &cone->center);
	double	a = dot(d, &cone->axis);
	double	c = dot(&x, &cone->axis);
	double	temp = 1 + cone->radius * cone->radius;
	double	b = 2.0 * (dot(d, &x) - temp * a * c);

	a = dot(d, d) - temp * a * a;
	c = dot(&x, &x) - temp * c * c;
	float  disc = b * b - 4*a*c;
	temp = 1/(2 * a);

	if (disc < 0.0f)
		return ((t_result ){INFINITY, INFINITY});
	disc = sqrt(disc);
	t_result res;
	res.t1 = (-b - disc) * temp;
	res.t2 = (-b + disc) * temp;
	return res;
}

t_result	intersect_ray_plane(t_pos *o, t_pos *d, t_plane *plane) // min == closest cone-> closest t
{
	double 		a;
	double 		b;
	t_pos		c;
	t_result	res;

	b = dot(d, &plane->normal);
	res.t1 = INFINITY;
	res.t2 = INFINITY;
	if (b > 0.0)
		return (res);
	c = vector_minus(o, &plane->center);
	a = dot(&c, &plane->normal);
	res.t1 = -(a / b);
	return (res);

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

t_result intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cylinder)
{
	double a;
	double b;
	double c;
	double discriminant;
	t_pos oc;
	t_result res;

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
	else if (obj->type == o_plane)
		return (intersect_ray_plane(o, d, &obj->objects->plane));
	else if (obj->type == o_cone)
		return (intersect_ray_cone(o, d, &obj->objects->cone));
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
