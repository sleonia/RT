#include "./includes/kernel.h"

static float3		matrix_rotation(float a, float b, float3 vec)
{
	float	x;
	float	z;
	float	y;

	x = vec[0];
	y = vec[1];
	z = vec[2];
	vec[0] = x * cos(b) + z * sin(b);
	vec[1] = (x * sin(b) - z * cos(b)) * sin(a) + y * cos(a);
	vec[2] = (z * cos(b) - x * sin(b)) + y * sin(a);
	return (vec);
}

static float		vector_len(float3 o)
{
	return(sqrt(o[0] * o[0] + o[1] * o[1] + o[2] * o[2]));
}

static float3		canvas_to_viewport(int x, int y)
{
	float3	vec;

	vec[0] = (float)x * VW / WIDTH;
	vec[1] = (float)y * VH / HEIGHT;
	vec[2] = D;
	return (vec);
}

////////////////////////////////////////////////////////
static float3	get_cone_normal(float3 start_ray, float3 ray, t_cone *obj, float intersect_dist)
{
	float3	ret_normal;
	float3	oc;
	float	m;

	// oc = vector_minus(start_ray, &obj->center);
	oc = start_ray - obj->center;
	// m = dot(ray, &obj->axis) * intersect_dist + dot(&oc, &obj->axis);
	m = dot(ray, obj->axis) * intersect_dist + dot(oc, obj->axis);
	// ret_normal = v_minus(v_plus(vector_on_number(ray, intersect_dist), oc), vector_on_number(&obj->axis, (1 + obj->tan * obj->tan) * m));
	ret_normal = (((ray * intersect_dist) + oc) - (obj->axis * (1 + obj->tan * obj->tan) * m));
	return (ret_normal);
}

static float3	get_cylinder_normal(t_cylinder *obj, float3 intersect_point)
{
	float3	n;
	float3	v;

	// v = vector_minus(intersect_point, &obj->center);
	v = intersect_point - obj->center;
	// n = vector_on_number(&obj->axis, dot(&v, &obj->axis));
	n = obj->axis * dot(v, obj->axis);
	// n = vector_minus(&v, &n);
	n = v - n;
	return (n);
}

static float3		get_obj_normal(float3 p, t_return *ret, float3 o, float3 d)
{
	float3		n;
	t_object	*obj;

	obj = ret->closest_object;
	if (obj->type == o_sphere)
		// n = vector_minus(p, &obj->objects->sphere.center);
		n = p - obj->objects->sphere.center;
	else if (obj->type == o_plane)
		n = obj->objects->plane.normal;
	else if (obj->type == o_cone)
		n = get_cone_normal(o, d, &obj->objects->cone, ret->closest_t);
	else if (obj->type == o_cylinder)
		n = get_cylinder_normal(&obj->objects->cylinder, p);
	// n = vector_div(&n, vector_len(&n));
	n = n / vector_len(n);
	return (n);
}
////////////////////////////////////////////////////////////////////

static float		computer_lighting(float3 p, float3 n, float3 v, int specular, __global t_scene *scene)
{
	float		intens;
	t_light		**tmp;
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
	tmp = scene->light;
	//костыль чтобы занулить l
	// l = vector_on_number(&l, 0);
	l = 0;
	while (i < 3)
	{
		if (tmp[i]->type == 'A' && !scene->off->ambient)
			intens += tmp[i]->intensity;
		else
		{
			if (tmp[i]->type == 'P' && !scene->off->point)
			{
				// l = vector_minus(&tmp[i]->position, p);
				l = tmp[i]->pos - p;
				t_max = 1.0;
			}
			else if (tmp[i]->type == 'D' && !scene->off->directional)
			{
				// l.x = tmp[i]->position.x;
				// l.y = tmp[i]->position.y;
				// l.z = tmp[i]->position.z;
				l = tmp[i]->pos;
				t_max = INFINITY;
			}
			// Проверка тени
			if (t_max)
			{
				shadow = closest_intersection(p, &l, 0.001, t_max, scene->object);
				if (shadow.closest_object != 0)
				{
					i++;
					continue ;
				}
				// Диффузность
				n_dot_l = dot(n, l);
				if (n_dot_l > 0)
					intens += tmp[i]->intensity * n_dot_l / (vector_len(n) * vector_len(l));
				// Зеркальность
				if (specular != -1)
				{
					// buf = vector_on_number(n, 2);
					buf = n * 2;
					// buf = vector_on_number(&buf, ft_dot(n, &l));
					buf = buf * dot(n, l);
					// r = vector_minus(&buf, &l);
					r = buf - l;
					r_dot_v = dot(r, v);
					if (r_dot_v > 0)
						intens += tmp[i]->intensity * pow(r_dot_v / (vector_len(r) * vector_len(v)), specular);
				}
			}
		}
		i++;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}

///////////////////////////////////////
static int			 trace_ray(float3 o, float3 d, float t_min, float t_max, __global t_scene *scene)
{
	float3 p;
	float3 n;
	float3 buf;
	float3 r;
	t_return ret;
	float c;
	int local_color;
	// int reflected_color;
	// float ref;

	// ret = closest_intersection(o, d, t_min, t_max, scene->object);
	//  был NULL
	if (!ret.closest_object)
		return (BLACK);
	// buf = vector_on_number(d, ret.closest_t);
	buf = d * ret.closest_t;
	// p = vector_pus(o, &buf);
	p = o + buf;
	// n = get_obj_normal(&p, &ret, o, d);!
	n = get_obj_normal(p, &ret, o, d);
	// n = vector_div(&n, vector_len(&n));!!!!
	// buf = vector_on_number(d, -1);
	buf = d * (-1);
	c = computer_lighting(p, n, buf, ret.closest_object->specular, scene);
	// local_color = color_scale(ret.closest_object->color, c);
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

__kernel void RT(__global int *arr, __global t_scene *scene)
{
	int 	color;
	int 	x;
	int 	y;
	int		pixel;

	pixel = get_global_id(0);
	x = pixel / HEIGHT % WIDTH - WIDTH / 2;
	y = HEIGHT / 2 - pixel / WIDTH;

	scene->view = matrix_rotation(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y));
	color = trace_ray(scene->cam->pos, scene->view, 1.0, INFINITY, scene);
	arr[pixel] = color;
}