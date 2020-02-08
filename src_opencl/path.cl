
#include "./includes/kernel.h"
#include "./includes/rt.h"

static float3		computer_lighting(float3 d, t_hitting *light_hit, __global t_object *obj, __global t_light *l,
		int count_obj, int count_light, float ambient, __global int *texture, __global int *texture_param)
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

__kernel void	path_trace(__global int *arr, __global t_cam *cam, __global t_object *object,
							__global t_light *light, __global int *texture, __global int *texture_param, int count_obj,
							int count_light, int skybox_id, int fsaa, float	ambient)
{
	int			x;
	int			y;
	float		cache_width = 1.f / WIDTH;
	float3		o;
	float3		d;
	float3		tmp_color;
	t_hitting	light_hit;

	x = get_global_id(0);
	y = get_global_id(1);
	d = (*cam).ox * ((float) (x + i * reverse(fsaa)) * cache_width - 0.5f) - (*cam).oy * ((float) (y + j * reverse(fsaa)) * cache_width - 0.5f) - (*cam).oz;
	d = normalize(d);
	o = (float3)cam->pos;
	for (int i = 0; i < 8; i++)
	{
		if (closest_intersection(o, d, count_obj, obj, &light_hit, texture, texture_param)
		{
			tmp_color += computer_lighting(d, &light_hit, object, light, count_obj, count_light, ambient, texture, texture_param);
		}
		else
			break ;
		o = light_hit->hit;
		d = ;
}