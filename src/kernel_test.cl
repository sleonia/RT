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
	red = get_light(RED(start), RED(end), v.x);
	green = get_light(GREEN(start), GREEN(end), v.y);
	blue = get_light(BLUE(start), BLUE(end), v.z);
	return ((red << 16) | (green << 8) | blue);
}

// static int 		color_scale(int	color, float c)
// {
// 	int 	red;
// 	int 	green;
// 	int 	blue;

// 	red = (color & 0xFF0000) >> 16;
// 	red = (int)((float)red * c);
// 	green = (color & 0x00FF00) >> 8;
// 	green = (int)((float)green * c);
// 	blue = (color & 0x0000FF);
// 	blue = (int)((float)blue * c);
// 	return ((red << 16) | (green << 8) | blue);
// }

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

// static float3		canvas_to_viewport(int x, int y)
// {
// 	float3	vec;

// 	vec.x = (float)x * VW / WIDTH;
// 	vec.y = (float)y * VH / HEIGHT;
// 	vec.z = D;
// 	return (vec);
// }

////////////////////////////////////////////////////////
// static float3	get_cone_normal(float3 *start_ray, float3 *ray, __global t_object *obj, float intersect_dist)
// {
// 	float3	ret_normal;
// 	float3	oc;
// 	float	m;

// 	oc = *start_ray - obj->center;
// 	m = dot(*ray, obj->axis) * intersect_dist + dot(oc, obj->axis);
// 	ret_normal = (((*ray * intersect_dist) + oc) - (obj->axis * (1 + obj->tan * obj->tan) * m));
// 	return (ret_normal);
// }

// static float3	get_cylinder_normal(__global t_object *obj, float3 *intersect_point)
// {
// 	float3	n;
// 	float3	v;

// 	v = *intersect_point - obj->center;
// 	n = obj->axis * dot(v, obj->axis);
// 	n = v - n;
// 	return (n);
// }

// static float3		get_obj_normal(float3 *p, t_return *ret, float3 *o, float3 *d, __global t_object *obj)
// {
// 	float3		n;

// 	if (obj[ret->closest_object].type == o_sphere)
// 		n = *p - obj[ret->closest_object].center;
// 	else if (obj[ret->closest_object].type == o_plane)
// 		n = obj[ret->closest_object].axis;
// 	else if (obj[ret->closest_object].type == o_cone)
// 		n = get_cone_normal(o, d, obj, ret->closest_t);
// 	else if (obj[ret->closest_object].type == o_cylinder)
// 		n = get_cylinder_normal(obj, p);
// 	n = n / vector_len(n);
// 	return (n);
// }
/////////////////////////////////////////////////////////////////////
static int	intersect_ray_sphere(float3 o, float3 d, __global t_sphere *sphere, float *dist_i)
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

static int    intersect_ray_cylinder(float3 o, float3 d, __global t_cylinder *cyl, float *dist_i)
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

static int	intersect_ray_plane(float3 o, float3 d, __global t_plane *pl, float *dist_i)
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
	*dist_i = (pl->dist_z - dot(o, pl->axis)) / a;
	if ((*dist_i) < 0.f)
		return (0);
	return (1);
}

static int   intersect_ray_cone(float3 o, float3 d, __global t_cone *cone, float *dist_i)
{
	float3	s;
	float3	q;
	float 	a;
	float 	b;
	float 	c;
	float 	discriminate;
	float 	t1;
	float	t2;

	s = d - cone->axis * dot(d, cone->axis);
	q = o - cone->center - cone->axis * dot((o - cone->center), cone->axis);
	a = cos(cone->tan) * cos(cone->tan) * dot(s, s) - sin(cone->tan) * sin(cone->tan) * dot(d, cone->axis) * dot(d, cone->axis);
	b = 2 * cos(cone->tan) * cos(cone->tan) * dot(s, q) - 2 * sin(cone->tan) *	sin(cone->tan) * dot(d, cone->axis) * dot(o - cone->center, cone->axis);
	c = cos(cone->tan) * cos(cone->tan) * dot(q, q) - sin(cone->tan) *	sin(cone->tan) * dot(o - cone->center, cone->axis) * dot(o - cone->center, cone->axis);
	discriminate = b * b - 4 * a * c;
	if (discriminate < 0.f)
		return (0);
	t1 = (-b + sqrt(discriminate)) / (2.f * a);
	t2 = (-b - sqrt(discriminate)) / (2.f * a);
	if (fabs(t1 - t2) < 0.000001f)
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
	// oc = o - cone->center;
	// a = dot(d, d) - (1 + cone->tan * cone->tan) * dot(d, cone->axis) * dot(d, cone->axis);
	// c = dot(oc, oc) - (1 + cone->tan * cone->tan) * dot(oc, cone->axis) * dot(oc, cone->axis);
	// b = dot(d, oc) - (1 + cone->tan * cone->tan) * dot(d, cone->axis) * dot(oc, cone->axis);
	// discr = b * b - a * c;
	// if (discr < 0.f )
	// 	return (0);
	// t1 = (-b - sqrt(discr))/(a);
	// t2 = (-b + sqrt(discr))/(a);
	// if (fabs(t1 - t2) < 0.000001)
	// 	return (0);
	// *dist_i = min(t1, t2);
	// if (*dist_i > 0.f)
	// {
	// 	if (acos(fabs(dot(d, cone->axis))) > cone->tan)
	// 		return (1);
	// 	return (2);
	// }
	// *dist_i = max(t1, t2);
	// if (*dist_i > 0.f)
	// {
	// 	if (acos(fabs(dot(d, cone->axis))) > cone->tan)
	// 		return (2);
	// 	return (1);
	// }
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
static int	closest_intersection(float3 o, float3 d, int count_obj, __global t_object *obj, t_hitting *light_hit)
{
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
			t12 = intersect_ray_sphere(o, d, &(obj + i)->object.sphere, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				light_hit->n = ft_normalize(light_hit->hit - obj[i].object.sphere.center);
				if (t12 == 2)
					light_hit->n *= -1.f;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		else if (obj[i].type == o_plane)
		{
			dist_i = 0.f;
			t12 = intersect_ray_plane(o, d, &(obj + i)->object.plane, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				light_hit->n = obj[i].object.plane.axis;
				if (dot(d, light_hit->n) > 0.f)
					light_hit->n *= -1.f;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
			}
		}
		else if (obj[i].type == o_cone)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cone(o, d, &(obj + i)->object.cone, &dist_i);
			if (t12 && dist_i < dist)
			{
				float dist_tmp;
				float3 norm = light_hit->n;
				float3 h = light_hit->hit;
				float3 orig = o;
				t_material m = light_hit->mat;

				dist_tmp = dist;
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				v = ft_normalize(light_hit->hit - obj[i].object.cone.center);
				light_hit->n = obj[i].object.cone.axis;
				light_hit->n = light_hit->n * ft_sign(dot(v, obj[i].object.cone.axis));
				light_hit->n = ft_normalize(v * dot(v, light_hit->n) - light_hit->n);
				if (t12 == 2)
					light_hit->n *= -1;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
				if (length(light_hit->hit - obj[i].object.cone.center) > obj[i].object.cone.length)
				{
					o = light_hit->hit + 0.001f * d;
					t12 = intersect_ray_cone(o, d, &(obj + i)->object.cone, &dist_i);
					dist = dist +dist_i;
					if (dist < dist_tmp)
					{
						light_hit->hit = o + d * dist_i;
						light_hit->mat = obj[i].material;
						//условие для uv mapping и наличия текстуры
						v = ft_normalize(light_hit->hit - obj[i].object.cone.center);
						light_hit->n = obj[i].object.cone.axis;
						light_hit->n = light_hit->n * ft_sign(dot(v, obj[i].object.cone.axis));
						light_hit->n = ft_normalize(v * dot(v, light_hit->n) - light_hit->n);
						if (t12 == 2)
							light_hit->n = -light_hit->n;
					}
					if (length(light_hit->hit - obj[i].object.cone.center) > obj[i].object.cone.length || dist > dist_tmp)
					{
						dist = dist_tmp;
						light_hit->n = norm;
						light_hit->hit = h;
						light_hit->mat = m;
					}
					o = orig;
				}
			}
		}
		else if (obj[i].type == o_cylinder)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cylinder(o, d, &(obj + i)->object.cylinder, &dist_i);
			if (t12 && dist_i < dist)
			{
				float dist_tmp;
				float3 norm = light_hit->n;
				float3 h = light_hit->hit;
				float3 orig = o;
				t_material m = light_hit->mat;

				dist_tmp = dist;
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				v = light_hit->hit - obj[i].object.cylinder.center;
				light_hit->n = obj[i].object.cylinder.axis * dot(v, obj[i].object.cylinder.axis);
				light_hit->n = ft_normalize(v - light_hit->n);
				if (t12 == 2)
					light_hit->n *= -1;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
				if (length(light_hit->hit - obj[i].object.cylinder.center) > obj[i].object.cylinder.length)
				{
					o = light_hit->hit + 0.001f * d;
					t12 = intersect_ray_cylinder(o, d, &(obj + i)->object.cylinder, &dist_i);
					dist = dist + dist_i;
					if (dist < dist_tmp)
					{
						light_hit->hit = o + d * dist_i;
						light_hit->mat = obj[i].material;
						//условие для uv mapping и наличия текстуры
						v = light_hit->hit - obj[i].object.cylinder.center;
						light_hit->n = obj[i].object.cylinder.axis * dot(v, obj[i].object.cylinder.axis);
						light_hit->n = -ft_normalize(v - light_hit->n);
					}
					if (length(light_hit->hit - obj[i].object.cylinder.center) > obj[i].object.cylinder.length || dist > dist_tmp)
					{
						dist = dist_tmp;
						light_hit->n = norm;
						light_hit->hit = h;
						light_hit->mat = m;
					}
					o = orig;
				}
			}
		}	
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
// 	t_hitting	shadow_hit;

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
// 				shadow = closest_intersection(p, &l, 0.001, t_max, 6, object, &shadow_hit);
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

static float3		computer_lighting(float3 d, t_hitting *light_hit, __global t_object *obj, __global t_light *l, int count_obj, int count_light, float ambient)
{
	float		light_dist = 0;
	float3		light_dir = (float3)0;
	float		a = 0.f;
	float		b = 0.f;
	t_hitting	shadow_hit;
	int			i = 0;
	float3		r = (float3)0;
	float		e = 0;

	shadow_hit.n = (float3)0;
	shadow_hit.hit = (float3)0;
	while (i < count_light)
	{
		light_dir = ft_normalize(l[i].pos - light_hit->hit);
		light_dist = ft_length(l[i].pos - light_hit->hit);
		if (dot(light_dir, light_hit->n) > 0)
		{
			float3 tmp = l[i].pos;			
			if (!closest_intersection(tmp, -light_dir, count_obj, obj, &shadow_hit) ||	(length(shadow_hit.hit - l[i].pos) > light_dist - 0.1f && length(shadow_hit.hit - l[i].pos) < light_dist + 0.1f))
			{
				a += dot(light_dir, light_hit->n) * l[i].intensity;
				b += pow(max(0.f, -dot(light_hit->n * 2.f * dot(light_dir, light_hit->n) - light_dir, d)), light_hit->mat.sp_ex) * l[i].intensity;
			}
		}
		++i;
	}
	r = light_hit->mat.color * (a + ambient) * light_hit->mat.al.x + (float3)(1) * light_hit->mat.al.y * b;
	e = max(max(r.x, r.y), r.z);
	if (e > 1.f)
		return (r * (1.f / e));
	return (r);
}

static float3	uv_mapping_for_skybox(__global int *skybox, float3 d, int tex_width, int tex_height)
{
	float3	vec;
	float 	v;
	float 	u;
	// int		coord_x;
	// int		coord_y;
	int		coord;

	vec = -d;
	// vec = normalize(vec);
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f + (asin(vec.y) / M_PI_F);
	// float2 uv = (float2)(u, v);


	// coord_x = (int)(u * tex_width);
	// coord_y = (int)(v * tex_height) * tex_width;
	coord = (int)(u * tex_width) + (int)(v * tex_height) * tex_width;
	// coord += prev_texture_size[screen->skybox_id];

	// color_uv.x = (RED(skybox[coord])) * 0.00392156862f;
	// color_uv.y = (GREEN(skybox[coord])) * 0.00392156862f;
	// color_uv.z = (BLUE(skybox[coord])) * 0.00392156862f;
	return ((float3){(RED(skybox[coord]) * 0.00392156862f), (GREEN(skybox[coord]) * 0.00392156862f), (BLUE(skybox[coord]) * 0.00392156862f)});
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
	t_hitting	light_hit;
	int count_light = 1;
	float	ambient = 0.2f;
	float cache_width = 1.f / WIDTH;
	int		fsaa = 0;

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

	// int i = 1;
	//Отправлять размеры текстуры, колличество объектов и количество источников света и саму текстуру

			if (closest_intersection(o, d, count_obj, object, &light_hit))
			{
				color += computer_lighting(d, &light_hit, object, light, count_obj, count_light, ambient);
			}
//	// if (1)
//	// {
//	// 	float ambient = 0.2f;
//	// 	int count_light = 1;
//	// 	trace_ray(o, d, count_obj, count_light, ambient, object, light, &light_hit, &color);
		// color_tmp[0] = help.color;
		// ref_tmp[0] = help.ref;
		// while (i < 3)
		// {
		// 	help = trace_ray(&help.p, &help.r, count_obj, object, light, &light_hit, &color);
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
		// skybox
			else if (1)
			{			
				color += uv_mapping_for_skybox(skybox, d, 8192, 4096);
			}
			else
				color += 0;
		}
	}
	color = color / ((fsaa + 1) * (fsaa + 1));
	pixel = y * WIDTH + x;
	arr[pixel] = get_color(color);
}

//Заменил рекурсию на цикл, надо все проверить почему при маленьком tmin рассыпается
//Реализовать path tracing
//Разбиение экрана на блоки