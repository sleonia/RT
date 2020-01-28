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
	vec.z = (z * cos(b) - x * sin(b)) * cos(a) + y * sin(a);
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
static float3	get_cone_normal(float3 *start_ray, float3 *ray, __global t_object *obj, float intersect_dist)
{
	float3	ret_normal;
	float3	oc;
	float	m;

	oc = *start_ray - obj->center;
	m = dot(*ray, obj->axis) * intersect_dist + dot(oc, obj->axis);
	ret_normal = (((*ray * intersect_dist) + oc) - (obj->axis * (1 + obj->tan * obj->tan) * m));
	return (ret_normal);
}

static float3	get_cylinder_normal(__global t_object *obj, float3 *intersect_point)
{
	float3	n;
	float3	v;

	v = *intersect_point - obj->center;
	n = obj->axis * dot(v, obj->axis);
	n = v - n;
	return (n);
}

static float3		get_obj_normal(float3 *p, t_return *ret, float3 *o, float3 *d, __global t_object *obj)
{
	float3		n;

	if (obj[ret->closest_object].type == o_sphere)
		n = *p - obj[ret->closest_object].center;
	else if (obj[ret->closest_object].type == o_plane)
		n = obj[ret->closest_object].axis;
	else if (obj[ret->closest_object].type == o_cone)
		n = get_cone_normal(o, d, obj, ret->closest_t);
	else if (obj[ret->closest_object].type == o_cylinder)
		n = get_cylinder_normal(obj, p);
	n = n / vector_len(n);
	return (n);
}
/////////////////////////////////////////////////////////////////////
static float2	intersect_ray_sphere(float3 *o, float3 *d, __global t_object *sphere)
{
	float3		oc;
	float		k1;
	float		k2;
	float		k3;
	float2	res;

	oc = *o - sphere->center;
	k1 = dot(*d, *d);
	k2 = 2 * dot(oc, *d);
	k3 = dot(oc, oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.x = INFINITY;
		res.y = INFINITY;
		return (res);
	}
	res.x = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.y = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	return (res);
}

static float2    intersect_ray_cylinder(float3 *o, float3 *d, __global t_object *cyl)
{
	float3 oc;
	float  a;
	float  b;
	float  c;
	float  discr;
	float2    res;

	oc = *o - cyl->center;
	a = dot(*d, *d) - dot(*d, cyl->axis) * dot(*d, cyl->axis);
	c = dot(oc, oc) - dot(oc, cyl->axis) * dot(oc, cyl->axis) - cyl->radius * cyl->radius;
	b = dot(*d, oc) - dot(*d, cyl->axis) * dot(oc, cyl->axis);
	discr = b * b - a * c;
	if (discr < 0.0 )
	{
		res.x = INFINITY;
		res.y = INFINITY;
	}
	else
	{
		res.x = (-b - sqrt(discr))/(a);
		res.y = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static float2	intersect_ray_plane(float3 *o, float3 *d, __global t_object *pl)
{
	float3		oc;
	float3		min;
	float		t;
	float2		res;

	oc = *o - pl->center;
	min = oc * (-1);
	t = dot(min, pl->axis) / dot(*d, pl->axis);
	res.x = t;
	res.y = INFINITY;
	return (res);
}

static float2    intersect_ray_cone(float3 *o, float3 *d, __global t_object *cone)
{
	float3 oc;
	float  a;
	float  b;
	float  c;
	float  discr;
	float2    res;

	oc = *o - cone->center;
	a = dot(*d, *d) - (1 + cone->tan * cone->tan) * dot(*d, cone->axis) * dot(*d, cone->axis);
	c = dot(oc, oc) - (1 + cone->tan * cone->tan) * dot(oc, cone->axis) * dot(oc, cone->axis);
	b = dot(*d, oc) - (1 + cone->tan * cone->tan) * dot(*d, cone->axis) * dot(oc, cone->axis);
	discr = b * b - a * c;
	if (discr < 0.0 )
	{
		res.x = INFINITY;
		res.y = INFINITY;
	}
	else
	{
		res.x = (-b - sqrt(discr))/(a);
		res.y = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static float2	get_intersect(float3 *o, float3 *d, __global t_object *obj)
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
static t_return	closest_intersection(float3 *o, float3 *d, float t_min, float t_max, __global t_object *object)
{
	float2	res;
	int 		i;
	t_return	ret;

	ret.closest_t = INFINITY;
	ret.closest_object = -1;
	i = 0;
	while (i < 6)
	{
		res = get_intersect(o, d, &object[i]);
		if (res.y >= t_min && res.y <= t_max && res.y < ret.closest_t)
		{
			ret.closest_t = res.y;
			ret.closest_object = i;
		}
		if (res.x >= t_min && res.x <= t_max && res.x < ret.closest_t)
		{
			ret.closest_t = res.x;
			ret.closest_object = i;
		}	
		i++;
	}
	return (ret);
}
/////////////////////////////////////
static float3		reflect_ray(float3 *r, float3 *n)
{
	float3	ret;
	
	ret = *n * 2 * dot(*r, *n) - *r;
	return (ret);
}
///////////////////////////////////////////////////
static float		computer_lighting(float3 *p, float3 *n, float3 *v, int specular, __global t_object *object, __global t_light *light)
{
	float3		l;
	float3		r;
	float3		buf;
	float		intens;
	float		n_dot_l;
	float		r_dot_v;
	float		t_max;
	int 		i;
	t_return	shadow;

	i = 0;
	intens = 0.0;
	l = 0;
	while (i < 3)
	{
		if (light[i].type == 'A')
			intens += light[i].intensity;
		else
		{
			if (light[i].type == 'P')
			{
				l = light[i].pos - *p;
				t_max = 1.0;
			}
			else if (light[i].type == 'D')
			{
				l = light[i].pos;
				t_max = INFINITY;
			}
			// Проверка тени
			if (t_max)
			{
				shadow = closest_intersection(p, &l, 0.001, t_max, object);
				if (shadow.closest_object != -1)
				{
					i++;
					continue ;
				}
				// Диффузность
				n_dot_l = dot(*n, l);
				if (n_dot_l > 0)
					intens += light[i].intensity * n_dot_l / (vector_len(*n) * vector_len(l));
				// Блеск
				if (specular != -1)
				{
					r = reflect_ray(&l, n);
					r_dot_v = dot(r, *v);
					if (r_dot_v > 0)
						intens += light[i].intensity * pow(r_dot_v / (vector_len(r) * vector_len(*v)), specular);
				}
			}
		}
		i++;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}

static t_help			 trace_ray(float3 *o, float3 *d, float t_min, float t_max, __global t_object *object, __global t_light *light)
{
	float3		p;
	float3		n;
	float3		buf;
	float3		r;
	float		c;
	int			local_color;
	t_return	ret;
	t_help		help;

	ret = closest_intersection(o, d, t_min, t_max, object);
	if (ret.closest_object ==  -1)
	{
		help.color = BLACK;
		help.r = 0;
		help.p = 0;
		help.ref = 0;
		return (help);
	}
	buf = *d * ret.closest_t;
	p = *o + buf;
	n = get_obj_normal(&p, &ret, o, d, object);
	buf = *d * (-1);
	c = computer_lighting(&p, &n, &buf, object[ret.closest_object].specular, object, light);
	local_color = color_scale(object[ret.closest_object].color, c);
	r = reflect_ray(&buf, &n);
	help.color = local_color;
	help.p = p;
	help.r = r;
	help.ref = object[ret.closest_object].reflective;
	return (help);
}

__kernel void RT(__global int *arr, __global t_cam *cam, __global t_object *object, __global t_light *light, __global int *background)
{
	int 	x;
	int 	y;
	int		pixel;
	float3	d;
	float3	o;
	float3	ref_tmp;
	int3	color_tmp;
	t_help	help;

	pixel = get_global_id(0);
	x = pixel % WIDTH - WIDTH / 2;
	y = HEIGHT / 2 - pixel / WIDTH;
	d = matrix_rotation(cam->a, cam->b, canvas_to_viewport(x, y));
	o = (float3)cam->pos;
	int i = 1;
	help = trace_ray(&o, &d, 1.0f, INFINITY, object, light);
	color_tmp[0] = help.color;
	ref_tmp[0] = help.ref;
	while (i < 3)
	{
		help = trace_ray(&help.p, &help.r, 0.001f, INFINITY, object, light);
		// if (help.ref == 0)
		// {
		// 	color_tmp[i] = help.color;
		// 	i++;
		// 	break ;
		// }		
		color_tmp[i] = help.color;
		ref_tmp[i] = help.ref;
		i++;
	}
	while (--i > 0)
	{
		color_tmp[i - 1] = color_scale(color_tmp[i - 1], 1 - ref_tmp[i - 1]) + color_scale(color_tmp[i], ref_tmp[i - 1]);
	}
	// if (color_tmp[0] == BLACK)
	// {
	// 	color_tmp[0] = background[pixel];
	// }
	arr[pixel] = color_tmp[0];
}

//Заменил рекурсию на цикл, надо все проверить почему при маленьком tmin рассыпается
//Реализовать path tracing
//Как пускать не 1 луч в пиксель, а 4 луча на границах для точности
//Разбиение экрана на блоки
//Дерьмовый бэкграунд