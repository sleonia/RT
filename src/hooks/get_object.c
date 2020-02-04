#include "rt.h"

static int	intersect_ray_sphere(cl_float3 o, cl_float3 d, t_sphere *sphere, float *dist_i)
{
	cl_float3	oc;
	float		k1;
	float		k2;
	float		k3;

	oc = cl_minus(o,sphere->center);
	k1 = dot(d, d);
	k2 = 2 * dot(oc, d);
	k3 = dot(oc, oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
		return (0);
	*dist_i = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.002f)
		return (1);
	*dist_i = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.002f)
		return (2);
	return (0);
}

static int    intersect_ray_cylinder(cl_float3 o, cl_float3 d, t_cylinder *cyl, float *dist_i)
{
	float		b;
	cl_float3	s;
	cl_float3	q;
	float		c;
	float		discriminate;

	s = cl_minus(d, cl_mult_n(cyl->axis, dot(d, cyl->axis)));
	q = cl_minus(o, cyl->center);
	q = cl_minus(q, cl_mult_n(cyl->axis, dot(q, cyl->axis)));
	b = 2 * dot(s, q);
	c = dot(q, q) - cyl->radius * cyl->radius;
	discriminate = b * b - 4 * dot(s, s) * c;
	if (fabs(discriminate) < 0.000001f)
		return (0);
	if (discriminate < 0.f)
		return (0);
	*dist_i = (-b - sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.002f)
		return (1);
	*dist_i = (-b + sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.002f)
		return (2);
	return (0);
}

static int	intersect_ray_plane(cl_float3 o, cl_float3 d, t_plane *pl, float *dist_i)
{
	float	a;

	cl_normalize(&pl->axis);
	cl_normalize(&d);
	a = dot(d, pl->axis);
	if (fabs(a) < 0.000001f)
		return (0);
	*dist_i = (pl->dist - dot(o, pl->axis)) / a;
	if ((*dist_i) < 0.02f)
		return (0);
	return (1);
}

static int   intersect_ray_cone(cl_float3 o, cl_float3 d, t_cone *cone, float *dist_i)
{
	cl_float3	s;
	cl_float3	q;
	float	 	a;
	float	 	b;
	float	 	c;
	float	 	discriminate;
	float	 	t1;
	float		t2;

	s = cl_minus(d, cl_mult_n(cone->axis, dot(d, cone->axis)));
	q = cl_minus(o, cl_minus(cone->center, cl_mult_n(cone->axis, dot((cl_minus(o, cone->center)), cone->axis))));
	a = cos(cone->tan) * cos(cone->tan) * dot(s, s) - sin(cone->tan) * sin(cone->tan) * dot(d, cone->axis) * dot(d, cone->axis);
	b = 2 * cos(cone->tan) * cos(cone->tan) * dot(s, q) - 2 * sin(cone->tan) *	sin(cone->tan) * dot(d, cone->axis) * dot(cl_minus(o, cone->center), cone->axis);
	c = cos(cone->tan) * cos(cone->tan) * dot(q, q) - sin(cone->tan) *	sin(cone->tan) * dot(cl_minus(o, cone->center), cone->axis) * dot(cl_minus(o, cone->center), cone->axis);
	discriminate = b * b - 4 * a * c;
	if (discriminate < 0.f)
		return (0);
	t1 = (-b + sqrt(discriminate)) / (2.f * a);
	t2 = (-b - sqrt(discriminate)) / (2.f * a);
	if (fabs(t1 - t2) < 0.002f)
		return (0);
	*dist_i = MIN(t1, t2);
	if (*dist_i > 0.002f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (1);
		return (2);
	}
	*dist_i = MAX(t1, t2);
	if (*dist_i > 0.002f)
	{
		if (acos(fabs(dot(d, cone->axis))) > cone->tan)
			return (2);
		return (1);
	}
	return (0);
}

t_object		*get_object(t_scene *scene, int x, int y)
{
	cl_float3	d;
	t_object	*closest;
	t_object	*obj;
	float		dist;
	float		dist_i;
	int			i;
	int			t12;
	cl_float3	o;

	d = cl_minus(cl_mult_n(scene->cam.ox, ((float)x * 1.f / WIDTH) - 0.5f), cl_mult_n(scene->cam.oy, ((float)y * 1.f / WIDTH) -0.5f));
	d = cl_minus(d, scene->cam.oz);
	cl_normalize(&d);
	o = (cl_float3)scene->cam.pos;
	obj = scene->object;
	dist = 10000.f + 1.f;
	i = 0;
	while (i < scene->count_objects)
	{
		if (obj[i].type == o_sphere)
		{
			dist_i = 0.f;
			t12 = intersect_ray_sphere(o, d, &(obj + i)->object.sphere, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				*closest = obj[i];
			}
		}
		else if (obj[i].type == o_plane)
		{
			dist_i = 0.f;
			t12 = intersect_ray_plane(o, d, &(obj + i)->object.plane, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				*closest = obj[i];		
			}
		}
		else if (obj[i].type == o_cone)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cone(o, d, &(obj + i)->object.cone, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				*closest = obj[i];
			}
		}
		else if (obj[i].type == o_cylinder)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cylinder(o, d, &(obj + i)->object.cylinder, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				*closest = obj[i];
			}
		}	
		i++;
	}
	if (dist < 10000.f)
		return (closest);
	return (NULL);
}