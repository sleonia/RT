
#include "./includes/kernel.h"
#include "./includes/rt.h"

static float	reverse(int n)
{
	if (n != 0)
		return (1.0f / n);
	return (0);
}

int  ft_sign(float a)
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

int				get_color(float3 v)
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

static float3		computer_lighting(float3 d, t_hitting *light_hit, __global t_object *obj, __global t_light *l, int count_obj, int count_light, float ambient, __global int *texture, __global int *texture_param, int move_on)
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
	if (move_on == 1)
		count_light = 1;
	while (i < count_light)
	{
		light_dir = normalize(l[i].pos - light_hit->hit);
		light_dist = length(l[i].pos - light_hit->hit);
		if (dot(light_dir, light_hit->n) > 0)
		{
			float3 tmp = l[i].pos;			
			if (!closest_intersection(tmp, -light_dir, count_obj, obj, &shadow_hit, texture, texture_param, move_on) ||	(length(shadow_hit.hit - l[i].pos) > light_dist - 0.1f && length(shadow_hit.hit - l[i].pos) < light_dist + 0.1f))
			{
				a += dot(light_dir, light_hit->n) * l[i].intensity;
				b += pow(max(0.f, -dot(light_hit->n * 2.f * dot(light_dir, light_hit->n) - light_dir, d)), light_hit->mat.specular) * l[i].intensity;
			}
		}
		i++;
	}
	r = light_hit->mat.color * (a + ambient) * light_hit->mat.ambient + (float3)(1) * light_hit->mat.diffuse * b;
	e = max(max(r.x, r.y), r.z);
	if (e > 1.f)
		return (r * (1.f / e));
	return (r);
}

__kernel void RT(__global int *arr, __global t_cam *cam, __global t_object *object, __global t_light *light, __global int *texture, __global int *texture_param, int count_obj, int count_light, int skybox_id, int fsaa, float	ambient, int move_on)
{
	int 	x;
	int 	y;
	int		pixel;
	float3	d;
	float3	o;
	float3	color = (float3)0;
	t_hitting	light_hit;
	float cache_width = 1.f / WIDTH;
	int		cnt_reflection;
	float3	tmp_color;
	int		depth = 4;

	x = get_global_id(0);
	y = get_global_id(1);
	if (move_on == 1)
	{
		fsaa = 0;
		depth = 1;
	}
	for (int i = -fsaa * 0.5f; i <= fsaa * 0.5f; i++)
	{
		for (int j = -fsaa * 0.5f; j <= fsaa * 0.5f; j++)
		{
			d = (*cam).ox * ((float) (x + i * reverse(fsaa)) * cache_width - 0.5f) - (*cam).oy * ((float) (y + j * reverse(fsaa)) * cache_width - 0.5f);
			d = d - (*cam).oz;
			d = normalize(d);
			o = (float3)cam->pos;
			tmp_color = (float3)0;
			cnt_reflection = 0;
			while (cnt_reflection < depth)
			{
				cnt_reflection++;
				if (closest_intersection(o, d, count_obj, object, &light_hit, texture, texture_param, move_on))
				{
					tmp_color += computer_lighting(d, &light_hit, object, light, count_obj, count_light, ambient, texture, texture_param, move_on);
					if (light_hit.mat.reflection > 0.00001f)
					{
						tmp_color *= (1 - light_hit.mat.reflection);
						o = light_hit.hit;
						d = normalize(reflect_ray(d, light_hit.n));
					}
					else if (light_hit.mat.refraction > 0.00001f)
					{
						o = light_hit.hit - light_hit.n * 0.003f;
						d = normalize(refract_ray(d, light_hit.n, light_hit.mat.refraction));
					}
					else
						break ;
				}
				else if (skybox_id != -1 && !move_on)
				{
					tmp_color += uv_mapping_for_skybox(texture, d, texture_param, skybox_id);
					// break ;
				}
			}
			tmp_color /= (float)cnt_reflection;
			color += tmp_color;
		}
	}
	color = color / (float)((fsaa + 1) * (fsaa + 1));
	pixel = y * WIDTH + x;
	arr[pixel] = get_color(color);
}
