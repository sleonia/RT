#include "./includes/kernel.h"

static int 		color_scale(int	color, float c)
{
	int 	red;
	int 	green;
	int 	blue;

	red = (color & 0xFF0000) >> 16;
	red = (int)((float)red * c);
	green = (color & 0x00FF00) >> 8;
	green = (int)((float)green * c);
	blue = (color & 0x0000FF);
	blue = (int)((float)blue * c);
	return ((red << 16) | (green << 8) | blue);
}

static float3		matrix_rotation(float a, float b, float3 vec)
{
	float	x;
	float	z;
	float	y;

	x = vec.x;
	y = vec.y;
	z = vec.z;
	vec.x = x * cos(b) + z * sin(b);
	vec.y = (x * sin(b) - z * cos(b)) * sin(a) + y * cos(a);
	vec.z = (z * cos(b) - x * sin(b)) + y * sin(a);
	return (vec);
}

static float		vector_len(float3 o)
{
	return(sqrt(o.x * o.x + o.y * o.y + o.z * o.z));
}

static float3		canvas_to_viewport(int x, int y)
{
	float3	vec;

	vec.x = (float)x * VW / WIDTH;
	vec.y = (float)y * VH / HEIGHT;
	vec.z = D;
	return (vec);
}

////////////////////////////////////////////////////////
static float3	get_cone_normal(float3 *start_ray, __global float3 *ray, __global t_object *obj, float intersect_dist)
{
	float3	ret_normal;
	float3	oc;
	float	m;

	// oc = vector_minus(start_ray, &obj->center);
	oc = *start_ray - obj->center;
	// m = dot(ray, &obj->axis) * intersect_dist + dot(&oc, &obj->axis);
	m = dot(*ray, obj->axis) * intersect_dist + dot(oc, obj->axis);
	// ret_normal = v_minus(v_plus(vector_on_number(ray, intersect_dist), oc), vector_on_number(&obj->axis, (1 + obj->tan * obj->tan) * m));
	ret_normal = (((*ray * intersect_dist) + oc) - (obj->axis * (1 + obj->tan * obj->tan) * m));
	return (ret_normal);
}

static float3	get_cylinder_normal(__global t_object *obj, float3 *intersect_point)
{
	float3	n;
	float3	v;

	// v = vector_minus(intersect_point, &obj->center);
	v = *intersect_point - obj->center;
	// n = vector_on_number(&obj->axis, dot(&v, &obj->axis));
	n = obj->axis * dot(v, obj->axis);
	// n = vector_minus(&v, &n);
	n = v - n;
	return (n);
}

static float3		get_obj_normal(float3 *p, t_return *ret, float3 *o, __global float3 *d, __global t_object *obj)
{
	float3		n;
	// t_object	*obj;

	// obj = ret->closest_object;
	if (obj[ret->closest_object].type == o_sphere)
		// n = vector_minus(p, &obj->objects->sphere.center);
		n = *p - obj[ret->closest_object].center;
	else if (obj[ret->closest_object].type == o_plane)
		n = obj[ret->closest_object].normal;
	else if (obj[ret->closest_object].type == o_cone)
		n = get_cone_normal(o, d, obj, ret->closest_t);
	else if (obj[ret->closest_object].type == o_cylinder)
		n = get_cylinder_normal(obj, p);
	// n = vector_div(&n, vector_len(&n));
	n = n / vector_len(n);
	return (n);
}
/////////////////////////////////////////////////////////////////////
static t_result	intersect_ray_sphere(float3 *o, __global float3 *d, __global t_object *sphere)
{
	float3		oc;
	float		k1;
	float		k2;
	float		k3;
	t_result	res;


	// oc = vector_minus(o, &sphere->center);
	oc = *o - sphere->center;
	k1 = dot(*d, *d);
	k2 = 2 * dot(oc, *d);
	k3 = dot(oc, oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	return (res);
}

static t_result    intersect_ray_cylinder(float3 *o, __global float3 *d, __global t_object *cyl)
{
	t_result    res;
	float3 oc;
	float  a;
	float  b;
	float  c;
	float  discr;

	// oc = vector_minus(o, &cyl->center);
	oc = *o - cyl->center;
	a = dot(*d, *d) - dot(*d, cyl->axis) * dot(*d, cyl->axis);
	c = dot(oc, oc) - dot(oc, cyl->axis) * dot(oc, cyl->axis) - cyl->radius * cyl->radius;
	b = dot(*d, oc) - dot(*d, cyl->axis) * dot(oc, cyl->axis);
	discr = b * b - a * c;
	if (discr < 0.0 )
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
	}
	else
	{
		res.t1 = (-b - sqrt(discr))/(a);
		res.t2 = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static t_result intersect_ray_plane(float3 *cam, __global float3 *view, __global t_object *pl)
{
	float		t;
	float3		oc;
	float3		min;
	t_result	res;

	// oc = vector_minus(cam,&pl->center);
	oc = *cam - pl->center;
	// min = vector_on_number(&oc,-1);
	min = oc * (-1);
	t = dot(min, pl->normal) / dot(*view, pl->normal);
	res.t1 = t;
	res.t2 = INFINITY;
	return (res);
}

static t_result    intersect_ray_cone(float3 *o, __global float3 *d, __global t_object *cone)
{
	t_result    res;
	float3 oc;
	float  a;
	float  b;
	float  c;
	float  discr;

	// oc = vector_minus(o, &cone->center);
	oc = *o - cone->center;
	a = dot(*d, *d) - (1 + cone->tan * cone->tan) * dot(*d, cone->axis) * dot(*d, cone->axis);
	c = dot(oc, oc) - (1 + cone->tan * cone->tan) * dot(oc, cone->axis) * dot(oc, cone->axis);
	b = dot(*d, oc) - (1 + cone->tan * cone->tan) * dot(*d, cone->axis) * dot(oc, cone->axis);
	discr = b * b - a * c;
	if (discr < 0.0 )
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
	}
	else
	{
		res.t1 = (-b - sqrt(discr))/(a);
		res.t2 = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static t_result	get_intersect(float3 *o, __global float3 *d, __global t_object *obj)
{
	if (obj->type == o_sphere)
		return (intersect_ray_sphere(o, d, obj));
	else if (obj->type == o_plane)
		return (intersect_ray_plane(o, d, obj));
	else if (obj->type == o_cone)
		return (intersect_ray_cone(o, d, obj));
	else
		return (intersect_ray_cylinder(o, d, obj));
}
////////////////////////////////////////////////////////////////////
static t_return	closest_intersection(float3 *o, __global float3 *d, float t_min, float t_max, __global t_object *object)
{
	t_result	res;
	// t_object	*tmp;
	t_return	ret;
	int 		i;

	ret.closest_t = INFINITY;
	ret.closest_object = 0;
	// tmp = (t_object *)object;
	// printf("%f ", tmp[2].reflective);
	i = 0;
	// printf("%d ", tmp[0]->specular);
	while (i < 4)
	{
		res = get_intersect(o, d, &object[i]);
		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_object = i;
		}
		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_object = i;
		}
		i++;
	}
	// printf("%f ", ret.closest_t);
	return (ret);
}
///////////////////////////////////////////////////
static float		computer_lighting(float3 *p, float3 *n, float3 *v, int specular, __global t_scene *scene, __global t_object *object, __global t_light *light)
{
	float		intens;
	// t_light		*tmp;
	float3		l;
	float		n_dot_l;
	float		r_dot_v;
	float3		r;
	float3		buf;
	t_return	shadow;
	float		t_max;
	int 		i;

	i = 0;
	intens = 0.0;
	// tmp = (t_light *)light;
	//костыль чтобы занулить l
	// l = vector_on_number(&l, 0);
	l = 0;
	while (i < 3)
	{
		// printf("%c ", light[i].type)
		// if (light[i].type == 'A' && !scene->off->ambient)
		if (light[i].type == 'A')
			intens += light[i].intensity;
		else
		{
			// if (light[i].type == 'P' && !scene->off->point)
			if (light[i].type == 'P')
			{
				// l = vector_minus(&tmp[i].position, p);
				l = light[i].pos - *p;
				t_max = 1.0;
			}
			// else if (light[i].type == 'D' && !scene->off->directional)
			else if (light[i].type == 'D')
			{
				// l.x = tmp[i]->position.x;
				// l.y = tmp[i]->position.y;
				// l.z = tmp[i]->position.z;
				l = light[i].pos;
				t_max = INFINITY;
			}
			// Проверка тени
			if (t_max)
			{
				// shadow = closest_intersection(p, l, 0.001, t_max, object);
				// if (shadow.closest_object < 0 && shadow.closest_object > 4)
				// {
				// 	i++;
				// 	continue ;
				// }
				// Диффузность
				n_dot_l = dot(*n, l);
				if (n_dot_l > 0)
					intens += light[i].intensity * n_dot_l / (vector_len(*n) * vector_len(l));
				// Зеркальность
				// if (specular != -1)
				// {
				// 	// buf = vector_on_number(n, 2);
				// 	buf = n * 2;
				// 	// buf = vector_on_number(&buf, ft_dot(n, &l));
				// 	buf = buf * dot(n, l);
				// 	// r = vector_minus(&buf, &l);
				// 	r = buf - l;
				// 	r_dot_v = dot(r, v);
				// 	if (r_dot_v > 0)
				// 		intens += tmp[i]->intensity * pow(r_dot_v / (vector_len(r) * vector_len(v)), specular);
				// }
			}
		}
		i++;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}

///////////////////////////////////////
static int			 trace_ray(float3 *o, __global float3 *d, float t_min, float t_max, __global t_scene *scene, __global t_object *object, __global t_light *light)
{
	float3 p;
	float3 n;
	float3 buf;
	// float3 r;
	t_return ret;
	float c;
	int local_color;
	// int reflected_color;
	// float ref;

	// printf("%f ", object[2].reflective);
	// printf("%f ", light[2].intensity);
	ret = closest_intersection(o, d, t_min, t_max, object);
	//  был NULL
	// printf("%f ", o.x);
	// printf("%f ", object[ret.closest_object].reflective);
	// if (!object[ret.closest_object])
	if (ret.closest_object < 0 && ret.closest_object > 4)
		return (BLACK);
	// buf = vector_on_number(d, ret.closest_t);
	buf = *d * ret.closest_t;
	// p = vector_pus(o, &buf);
	p = *o + buf;
	// n = get_obj_normal(&p, &ret, o, d);!
	n = get_obj_normal(&p, &ret, o, d, object);
	// printf("%f ", n.x);
	// n = vector_div(&n, vector_len(&n));!!!!
	// buf = vector_on_number(d, -1);
	buf = *d * (-1);
	c = computer_lighting(&p, &n, &buf, object[ret.closest_object].specular, scene, object, light);
	// printf("%f ", c);
	local_color = color_scale(object[ret.closest_object].color, c);
	return (local_color);
	// Проверка выхода из рекурсии
	// ref = ret.closest_object->reflective;
	// if (depth <= 0 || ref <= 0 || scene->off->reflect)
	// 	return (local_color);

	// //Рекурсивная часть отражения объектов
	// r = reflect_ray(&buf, &n);
	// reflected_color = trace_ray(&p, &r, 0.001, INFINITY, scene, depth - 1);
	// return (color_scale(local_color, 1 - ref) + color_scale(reflected_color, ref));
}

__kernel void RT(__global int *arr, __global t_scene *scene, __global t_object *object, __global t_light *light)
{
	int 	color;
	int 	x;
	int 	y;
	int		pixel;

	pixel = get_global_id(0);
	x = pixel % WIDTH - WIDTH / 2;
	y = HEIGHT / 2 - pixel / WIDTH;
	// printf("%f ", object[2].reflective);
	// printf("%f %f\n", scene->cam->a, scene->cam->b);
	scene->view = matrix_rotation(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y));
	// printf("%f %f %f\n", scene->view.x, scene->view.y, scene->view.z);
	// printf("%f ", scene->light[0]->intensity);
	color = trace_ray(&scene->cam->pos, &scene->view, 1.0, INFINITY, scene, object, light);
	// printf("%d %d\n", x, y);
	arr[pixel] = color;
	// printf("%d ", arr[pixel]);
}