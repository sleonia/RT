#include "./includes/kernel.h"
#include "./includes/rtv1.h"

static float3	ft_normalize(float3 vec)
{
	return (vec / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

static float	ft_length(float3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

static float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}

static int  ft_sign(float a)
{
	if (a > 0.001)
		return (1);
	if (a < -0.001)
		return (-1);
	return (0);
}

static int		get_light(int start, int end, float percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

static int		get_color(float3 v)
{
	int     red;
	int     green;
	int     blue;
	int 	start;
	int		end;
	float	e;

	e  = (max(max(v.x, v.y), v.z));
	if (e > 1.f)
		v *= 1.f / e;
	start = 0;
	end = 0xFFFFFF;
	red = get_light((start >> 16) & 0xFF, (end >> 16) & 0xFF, v.x);
	green = get_light((start >> 8) & 0xFF, (end >> 8) & 0xFF, v.y);
	blue = get_light(start & 0xFF, end & 0xFF, v.z);
	return ((red << 16) | (green << 8) | blue);
}

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
static int	intersect_ray_sphere(float3 o, float3 d, __global t_object *sphere, float *dist_i)
{
	float3		oc;
	float		k1;
	float		k2;
	float		k3;

	oc = o - sphere->center;
	k1 = dot(d, d);
	k2 = 2 * dot(oc, d);
	k3 = dot(oc, oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
		return (0);
	*dist_i = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.00001)
		return (1);
	*dist_i = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.00001)
		return (2);
	return (0);
}

static int    intersect_ray_cylinder(float3 o, float3 d, __global t_object *cyl, float *dist_i)
{
	float	b;
	float3	s;
	float3	q;
	float	c;
	float	discriminate;

	s = d - cyl->axis * dot(d, cyl->axis);
	q = o - cyl->center;
	q = q - cyl->axis * dot(q, cyl->axis);
	b = 2 * dot(s, q);
	c = dot(q, q) - cyl->radius * cyl->radius;
	discriminate = b * b - 4 * dot(s, s) * c;
	if (fabs(discriminate) < 0.000001f)
		return (0);
	if (discriminate < 0.f)
		return (0);
	*dist_i = (-b - sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.f)
		return (1);
	*dist_i = (-b + sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0)
		return (2);
	return (0);
}

static int	intersect_ray_plane(float3 o, float3 d, __global t_object *pl, float *dist_i)
{
	// float3		oc;
	// float3		min;

	// oc = *o - pl->center;
	// min = oc * (-1);
	// *dist_i = dot(min, pl->axis) / dot(*d, pl->axis);
	// if ((*dist_i < 0.f))
	// 	return (0);
	// return (1);
	float	a = 0;

	pl->axis = ft_normalize(pl->axis);
	d = ft_normalize(d);
	a = dot(d, pl->axis);
	if (fabs(a) < 0.000001f)
		return (0);
	*dist_i = (pl->tan - dot(o, pl->axis)) / a;
	if ((*dist_i) < 0.f)
		return (0);
	return (1);
}

static int   intersect_ray_cone(float3 o, float3 d, __global t_object *cone, float *dist_i)
{
	float3	oc;
	float 	a;
	float 	b;
	float 	c;
	float 	discr;
	float 	t1;
	float	t2;

	oc = o - cone->center;
	a = dot(d, d) - (1 + cone->tan * cone->tan) * dot(d, cone->axis) * dot(d, cone->axis);
	c = dot(oc, oc) - (1 + cone->tan * cone->tan) * dot(oc, cone->axis) * dot(oc, cone->axis);
	b = dot(d, oc) - (1 + cone->tan * cone->tan) * dot(d, cone->axis) * dot(oc, cone->axis);
	discr = b * b - a * c;
	if (discr < 0.f )
		return (0);
	t1 = (-b - sqrt(discr))/(a);
	t2 = (-b + sqrt(discr))/(a);
	if (fabs(t1 - t2) < 0.000001)
		return (0);
	*dist_i = min(t1, t2);
	if (*dist_i > 0.f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (1);
		return (2);
	}
	*dist_i = max(t1, t2);
	if (*dist_i > 0.f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (2);
		return (1);
	}
	return (0);
}

// static float2	get_intersect(float3 *o, float3 *d, __global t_object *obj)
// {
// 	if (obj->type == o_sphere)
// 		return (intersect_ray_sphere(o, d, obj));
// 	else if (obj->type == o_plane)
// 		return (intersect_ray_plane(o, d, obj));
// 	else if (obj->type == o_cone)
// 		return (intersect_ray_cone(o, d, obj));
// 	else
// 		return (intersect_ray_cylinder(o, d, obj));
// }
////////////////////////////////////////////////////////////////////
static int	closest_intersection(float3 o, float3 d, int count_obj, __global t_object *obj, t_lighting *lighting)
{
	// float2	res;
	// int 		i;
	// t_return	ret;

	float		dist;
	int			i;
	int			t12;
	float		dist_i;
	float3		v;

	dist = MAX_DIST + 1.f;
	i = 0;
	while (i < count_obj)
	{
		if (obj[i].type == o_sphere)
		{
			dist_i = 0.f;
			t12 = intersect_ray_sphere(o, d, (obj + i), &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				lighting->hit = o + d * dist_i;
				lighting->n = ft_normalize(lighting->hit - obj[i].center);
				if (t12 == 2)
					lighting->n *= -1.f;
				lighting->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		else if (obj[i].type == o_plane)
		{
			dist_i = 0.f;
			t12 = intersect_ray_plane(o, d, (obj + i), &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				lighting->hit = o + d * dist_i;
				lighting->n = obj[i].axis;
				if (dot(d, lighting->n) > 0.f)
					lighting->n *= -1.f;
				lighting->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		///////////////ДОДЕЛАТЬ
		else if (obj[i].type == o_cone)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cone(o, d, (obj + i), &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				lighting->hit = o + d * dist_i;
				v = ft_normalize(lighting->hit - obj[i].center);
				lighting->n = obj[i].axis;
				lighting->n = lighting->n * ft_sign(dot(v, obj[i].axis));
				lighting->n = ft_normalize(v * dot(v, lighting->n) - lighting->n);
				if (t12 == 2)
					lighting->n *= -1;
				lighting->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		else if (obj[i].type == o_cylinder)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cylinder(o, d, (obj + i), &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				lighting->hit = o + d * dist_i;
				v = lighting->hit - obj[i].center;
				lighting->n = obj[i].axis * dot(v, obj[i].axis);
				lighting->n = ft_normalize(v - lighting->n);
				if (t12 == 2)
					lighting->n *= -1;
				lighting->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		//////////////////
		// res = get_intersect(o, d, &object[i]);
		// if (res.y >= t_min && res.y <= t_max && res.y < ret.closest_t)
		// {
		// 	ret.closest_t = res.y;
		// 	ret.closest_object = i;
		// }
		// if (res.x >= t_min && res.x <= t_max && res.x < ret.closest_t)
		// {
		// 	ret.closest_t = res.x;
		// 	ret.closest_object = i;
		// }	
		i++;
	}
	return (dist < MAX_DIST);
}
/////////////////////////////////////
// static float3		reflect_ray(float3 *r, float3 *n)
// {
// 	float3	ret;
	
// 	ret = *n * 2 * dot(*r, *n) - *r;
// 	return (ret);
// }
///////////////////////////////////////////////////
// static float		computer_lighting(float3 *p, float3 *n, float3 *v, int specular, __global t_object *object, __global t_light *light)
// {
// 	float3		l;
// 	float3		r;
// 	// float3		buf;
// 	float		intens;
// 	float		n_dot_l;
// 	float		r_dot_v;
// 	float		t_max;
// 	int 		i;
// 	t_return	shadow;
// 	t_lighting	shadow_lighting;

// 	i = 0;
// 	intens = 0.0;
// 	l = 0;
// 	while (i < 3)
// 	{
// 		if (light[i].type == 'A')
// 			intens += light[i].intensity;
// 		else
// 		{
// 			if (light[i].type == 'P')
// 			{
// 				l = light[i].pos - *p;
// 				t_max = 1.0;
// 			}
// 			else if (light[i].type == 'D')
// 			{
// 				l = light[i].pos;
// 				t_max = MAX_DIST;
// 			}
// 			// Проверка тени
// 			if (t_max)
// 			{
// 				shadow = closest_intersection(p, &l, 0.001, t_max, 6, object, &shadow_lighting);
// 				if (shadow.closest_object != -1)
// 				{
// 					i++;
// 					continue ;
// 				}
// 				// Диффузность
// 				n_dot_l = dot(*n, l);
// 				if (n_dot_l > 0)
// 					intens += light[i].intensity * n_dot_l / (vector_len(*n) * vector_len(l));
// 				// Блеск
// 				if (specular != -1)
// 				{
// 					r = reflect_ray(&l, n);
// 					r_dot_v = dot(r, *v);
// 					if (r_dot_v > 0)
// 						intens += light[i].intensity * pow(r_dot_v / (vector_len(r) * vector_len(*v)), specular);
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	if (intens > 1.0)
// 		return (1.0);
// 	return (intens);
// }

static float3		computer_lighting_1(float3 d, t_lighting *lighting, __global t_object *obj, __global t_light *l, int count_obj, int count_light, float ambient)
{
	float		light_dist = 0;
	float3		light_dir = (float3)0;
	float		a = 0.f;
	float		b = 0.f;
	t_lighting	shadow_lighting;
	int			i = 0;
	float3		r = (float3)0;
	float		e = 0;

	shadow_lighting.n = (float3)0;
	shadow_lighting.hit = (float3)0;
	while (i < count_light)
	{
		light_dir = ft_normalize(l[i].pos - lighting->hit);
		light_dist = ft_length(l[i].pos - lighting->hit);
		if (dot(light_dir, lighting->n) > 0)
		{
			float3 tmp = l[i].pos;			
			if (!closest_intersection(tmp, -light_dir, count_obj, obj, &shadow_lighting) ||	(ft_length(shadow_lighting.hit - l[i].pos) > light_dist - 0.1f && ft_length(shadow_lighting.hit - l[i].pos) < light_dist + 0.1f))
			{
				a += dot(light_dir, lighting->n) * l[i].intensity;
				b += pow(max(0.f, -dot(lighting->n * 2.f * dot(light_dir, lighting->n) - light_dir, d)), lighting->mat.sp_ex) * l[i].intensity;
			}
		}
		i++;
	}
	//убрал из mat al.x al.y
	r = lighting->mat.color * (a + ambient) * lighting->mat.al.x + (float3)(1) * lighting->mat.al.y * b;
	e = max(max(r.x, r.y), r.z);
	if (e > 1.f)
		return (r * (1.f / e));
	return (r);
}

static int			 trace_ray(float3 o, float3 d, int count_obj, int count_light, float ambient, __global t_object *object, __global t_light *light, t_lighting *lighting, float3 *color)
{
	// float3		p;
	// float3		n;
	// float3		buf;
	// float3		r;
	// float		c;
	// int			local_color;
	// t_return	ret;
	// t_help		help;

	if (closest_intersection(o, d, count_obj, object, lighting))
	{
		*color += computer_lighting_1(d, lighting, object, light, count_obj, count_light, ambient);
	}
	else
		*color += 0;
	// if (ret.closest_object ==  -1)
	// {
	// 	help.color = BLACK;
	// 	help.r = 0;
	// 	help.p = 0;
	// 	help.ref = 0;
	// 	return (help);
	// }
	// buf = *d * ret.closest_t;
	// p = *o + buf;
	// n = get_obj_normal(&p, &ret, o, d, object);
	// buf = *d * (-1);
	// c = computer_lighting(&p, &n, &buf, object[ret.closest_object].specular, object, light);
	// local_color = color_scale(object[ret.closest_object].color, c);
	// r = reflect_ray(&buf, &n);
	// help.color = local_color;
	// help.p = p;
	// help.r = r;
	// help.ref = object[ret.closest_object].reflective;
	return (0);
}

__kernel void RT(__global int *arr, __global t_cam *cam, __global t_object *object, __global t_light *light, __global int *skybox, int count_obj)
{
	int 	x;
	int 	y;
	int		pixel;
	float3	d;
	float3	o;
	// float3	ref_tmp;
	// int3	color_tmp;
	float3	color = (float3)0;
	// t_help	help;
	t_lighting	lighting;
	int count_light = 1;
	float	ambient = 0.2;
	float cache_width = 1.f / WIDTH;
	int		fsaa = 4;

	// pixel = get_global_id(0);
	// x = pixel % WIDTH - WIDTH / 2;
	// y = HEIGHT / 2 - pixel / WIDTH;
	// y = HEIGHT / 2 - pixel / WIDTH;
	x = get_global_id(0);
	y = get_global_id(1);
	o = (float3)cam->pos;
////////////
	// d = matrix_rotation(cam->a, cam->b, canvas_to_viewport(x, y));
	for (int i = -fsaa * 0.5f; i <= fsaa * 0.5f; i++)
	{
		for (int j = -fsaa * 0.5f; j <= fsaa * 0.5f; j++)
		{
			d = (*cam).v1 * ((float) (x + i * reverse(fsaa)) * cache_width - 0.5f) - (*cam).v2 * ((float) (y + j * reverse(fsaa)) * cache_width - 0.5f);
			d = d - (*cam).center;
			d = normalize(d);
//////////
	////Два цикла с fsaa (сглаживание)
	////пересчет d с условиями сглаживания и поворота камеры

	// int i = 1;
	//Отправлять размеры текстуры, колличество объектов и количество источников света и саму текстуру

		//условие что пересеклось
			if (closest_intersection(o, d, count_obj, object, &lighting))
			{
				color += computer_lighting_1(d, &lighting, object, light, count_obj, count_light, ambient);
			}
//	// if (1)
//	// {
//	// 	float ambient = 0.2f;
//	// 	int count_light = 1;
//	// 	trace_ray(o, d, count_obj, count_light, ambient, object, light, &lighting, &color);
		// color_tmp[0] = help.color;
		// ref_tmp[0] = help.ref;
		// while (i < 3)
		// {
		// 	help = trace_ray(&help.p, &help.r, count_obj, object, light, &lighting, &color);
		// 	// if (help.ref == 0)
		// 	// {
		// 	// 	color_tmp[i] = help.color;
		// 	// 	i++;
		// 	// 	break ;
		// 	// }		
		// 	color_tmp[i] = help.color;
		// 	ref_tmp[i] = help.ref;
		// 	i++;
		// }
		// while (--i > 0)
		// {
		// 	color_tmp[i - 1] = color_scale(color_tmp[i - 1], 1 - ref_tmp[i - 1]) + color_scale(color_tmp[i], ref_tmp[i - 1]);
		// }
	// }
	//skybox
	// else if (0)
	// {

	// }
			else
				color += 0;
		}
	}
	color = color / ((fsaa + 1) * (fsaa + 1));
	//скейл цвета по сглаживанию    !!!!!!!!!!!!!!!!
	pixel = y * WIDTH + x;
	arr[pixel] = get_color(color);
}

//Заменил рекурсию на цикл, надо все проверить почему при маленьком tmin рассыпается
//Реализовать path tracing
//Как пускать не 1 луч в пиксель, а 4 луча на границах для точности
//Разбиение экрана на блоки
//Дерьмовый бэкграунд