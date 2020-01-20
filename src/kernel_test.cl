#include "./includes/kernel.h"
#include "./includes/rtv1.h"

static float3	ft_normalize(float3 vec)
{
	return (vec / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
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
	return (0);
}

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

static float3		reflect_ray(float3 r, float3 n)
{
	return (r - n * 2 * dot(r, n));
}

static float3 refract_ray(const float3 I, float3 N, float refractive_index)
{
	float		n = refractive_index;
	float		cosI = -(dot(N, I));
	float		sinT2;
	float		cosT;

	if (cosI < 0.f)
		cosI = -cosI;
	else
	{
		n = 1.f / n;
		N = -N;
	}
	sinT2 = n * n * (1.f - cosI * cosI);
	cosT = sqrt(1.f - sinT2);
	return (n * I + (n * cosI - cosT) * N);
}

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
		light_dist = length(l[i].pos - light_hit->hit);
		if (dot(light_dir, light_hit->n) > 0)
		{
			float3 tmp = l[i].pos;			
			if (!closest_intersection(tmp, -light_dir, count_obj, obj, &shadow_hit) ||	(length(shadow_hit.hit - l[i].pos) > light_dist - 0.1f && length(shadow_hit.hit - l[i].pos) < light_dist + 0.1f))
			{
				a += dot(light_dir, light_hit->n) * l[i].intensity;
				b += pow(max(0.f, -dot(light_hit->n * 2.f * dot(light_dir, light_hit->n) - light_dir, d)), light_hit->mat.sp_ex) * l[i].intensity;
			}
		}
		i++;
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
	int		coord;

	vec = -d;
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f + (asin(vec.y) / M_PI_F);
	coord = (int)(u * tex_width) + (int)(v * tex_height) * tex_width;
	// coord += prev_texture_size[screen->skybox_id];

	return ((float3){(RED(skybox[coord]) * 0.00392156862f), (GREEN(skybox[coord]) * 0.00392156862f), (BLUE(skybox[coord]) * 0.00392156862f)});
}

__kernel void RT(__global int *arr, __global t_cam *cam, __global t_object *object, __global t_light *light, __global int *skybox, int count_obj)
{
	int 	x;
	int 	y;
	int		pixel;
	float3	d;
	float3	o;
	float3	color = (float3)0;
	t_hitting	light_hit;
	int count_light = 1;
	float	ambient = 0.2f;
	float cache_width = 1.f / WIDTH;
	int		fsaa = 0;
	int		tex_width = 8192;
	int		tex_height = 4096;
	int		cnt_reflection = 0;

	x = get_global_id(0);
	y = get_global_id(1);
	o = (float3)cam->pos;
	for (int i = -fsaa * 0.5f; i <= fsaa * 0.5f; i++)
	{
		for (int j = -fsaa * 0.5f; j <= fsaa * 0.5f; j++)
		{
			d = (*cam).ox * ((float) (x + i * reverse(fsaa)) * cache_width - 0.5f) - (*cam).oy * ((float) (y + j * reverse(fsaa)) * cache_width - 0.5f);
			d = d - (*cam).oz;
			d = normalize(d);
	//Отправлять размеры текстуры, колличество объектов и количество источников света и саму текстуру
			while (cnt_reflection < 4)
			{
				cnt_reflection++;
				if (closest_intersection(o, d, count_obj, object, &light_hit) && cnt_reflection != 4)
				{
					color += computer_lighting(d, &light_hit, object, light, count_obj, count_light, ambient);
					if (light_hit.mat.reflection > 0.f)
					{
						o = light_hit.hit;
						d = ft_normalize(reflect_ray(d, light_hit.n));
					}
					else if (light_hit.mat.refraction > 0.f)
					{
						o = light_hit.hit - light_hit.n * 0.003f;
						d = ft_normalize(refract_ray(d, light_hit.n, light_hit.mat.refraction));
					}
					else
						break ;
				}
				else if (1)
				{			
					color += uv_mapping_for_skybox(skybox, d, tex_width, tex_height);
				}
			}
		}
	}
	color = color / cnt_reflection;
	color = color / ((fsaa + 1) * (fsaa + 1));
	pixel = y * WIDTH + x;
	arr[pixel] = get_color(color);
}

//Реализовать path tracing
//Разбиение экрана на блоки