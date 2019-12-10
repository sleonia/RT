#include "./includes/kernel.h"

static float3		canvas_to_viewport(int x, int y)
{
	return ((float3)((float)x * VW / WIDTH, (float)y * VH / HEIGHT, D));
}

static float2		intersect_ray_sphere(float3 *o, float3 *d, __global t_object *object)
{
	float3	c = object->center;
	float	r = object->radius;
	float3	oc;
	float	disc;
	float2	t;

	oc = *o - c;

	float k1 = dot(*d, *d);
	float k2 = 2 * dot(oc, *d);
	float k3 = dot(oc, oc) - r * r;

	disc = k2 * k2 - 4 * k1 * k3;
	if (disc < 0)
		return((float2)(INFINITY, INFINITY));
	t.x = (-k2 + sqrt(disc) / (2 * k1));
	t.y = (-k2 - sqrt(disc) / (2 * k1));
	return (t);
}

static int			trace_ray(float3 *o, float3 *d, float t_min, float t_max, __global t_object *object)
{
	float		closest_t = INFINITY;
	__global t_object	*closest_object = (void *)0;
	float2		t;

	for (int i = 0; i < 4; i++)
	{
		t = intersect_ray_sphere(o, d, &object[i]);
		if ((t_min <= t.x && t.x <= t_max) && t.x < closest_t)
		{
			closest_t = t.x;
			closest_object = &object[i];
		}
	}
	if (closest_object == (void*)0)
		return (BLACK);
	return (closest_object->color);
}

__kernel void RT(__global int *arr, __global t_cam *cam, __global t_object *object, __global t_light *light)
{
	int 	color;
	int 	x;
	int 	y;
	int		pixel;
	float3 d;
	float3 o;

	pixel = get_global_id(0);
	x = pixel % WIDTH - WIDTH / 2;
	y = HEIGHT / 2 - pixel / WIDTH;
	d = canvas_to_viewport(x, y);
	o = (float3)cam->pos;

	//До сюда все ок
	color = trace_ray(&o, &d, 1.0f, INFINITY, object);
	arr[pixel] = color;

}