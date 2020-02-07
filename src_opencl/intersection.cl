
#include "./includes/kernel.h"
#include "./includes/rt.h"

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
	if (*dist_i > 0.002f)
		return (1);
	*dist_i = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	if (*dist_i > 0.002f)
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

	float	z;

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
	if (*dist_i > 0.002f)
		if ((dot(cyl->axis, (d * *dist_i) + o - cyl->center) * dot(cyl->axis, (d * *dist_i) + o - cyl->center)) <= (cyl->length / 2) * (cyl->length / 2))
			return (1);
	*dist_i = (-b + sqrt(discriminate)) / (2 * dot(s, s));
	if (*dist_i > 0.002f)
		if ((dot(cyl->axis, (d * *dist_i) + o - cyl->center) * dot(cyl->axis, (d * *dist_i) + o - cyl->center)) <= (cyl->length / 2) * (cyl->length / 2))
			return (2);
	return (0);
}

static int	intersect_ray_plane(float3 o, float3 d, __global t_plane *pl, float *dist_i)
{
	float	a;

	pl->axis = normalize(pl->axis);
	d = normalize(d);
	a = dot(d, pl->axis);
	if (fabs(a) < 0.000001f)
		return (0);
	*dist_i = (pl->dist - dot(o, pl->axis)) / a;
	if ((*dist_i) < 0.02f)
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
	if (fabs(t1 - t2) < 0.002f)
		return (0);
	*dist_i = min(t1, t2);
	if (*dist_i > 0.002f)
	{
		if ((dot(cone->axis, (d * *dist_i) + o - cone->center) * dot(cone->axis, (d * *dist_i) + o - cone->center)) <= (cone->length / 2) * (cone->length / 2))
		{
			if (acos(fabs(dot(d, cone->axis))) > cone->tan)
				return (1);
			return (2);
		}
	}
	*dist_i = max(t1, t2);
	if (*dist_i > 0.002f)
	{
		if ((dot(cone->axis, (d * *dist_i) + o - cone->center) * dot(cone->axis, (d * *dist_i) + o - cone->center)) <= (cone->length / 2) * (cone->length / 2))
		{
			if (acos(fabs(dot(d, cone->axis))) > cone->tan)
				return (2);
			return (1);
		}
	}
	return (0);
}

static int	intersect_ray_parab(float3 o, float3 d, __global t_parab *parab, float *dist_i)
{
	float3	x;
	float 	a;
	float 	b;
	float 	c;
	float 	disc;

	x = o - parab->center;
	a = dot(d,d) - dot(d, parab->axis) * dot(d, parab->axis);
	b = 2.f * dot(d,x) - 2.f * dot(d, parab->axis) * (dot(x, parab->axis) + 2.f * parab->k);
	c = dot(x, x) - dot(x, parab->axis) * (dot(x, parab->axis) + 4.f * parab->k);
	disc = b * b - 4.f * a * c;
	if (disc < 0.00001f)
		return (0);
	*dist_i = (-b - sqrt(disc)) / (2.f * a);
	if (*dist_i > 0.002f)
		if ((dot(parab->axis, (d * *dist_i) + o - parab->center) * dot(parab->axis, (d * *dist_i) + o - parab->center)) <= (parab->length) * (parab->length))
			return (1);
	*dist_i = (-b + sqrt(disc)) / (2.f * a);
	if (*dist_i > 0.002f)
		if ((dot(parab->axis, (d * *dist_i) + o - parab->center) * dot(parab->axis, (d * *dist_i) + o - parab->center)) <= (parab->length) * (parab->length))
			return (2);
	return (0);
}

int	closest_intersection(float3 o, float3 d, int count_obj, __global t_object *obj, t_hitting *light_hit, __global int *texture, __global int *texture_param, int move_on)
{
	float		dist;
	int			i;
	int			t12;
	float		dist_i;
	float3		v;
	float2		uv;

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
				light_hit->n = normalize(light_hit->hit - obj[i].object.sphere.center);
				if (t12 == 2)
					light_hit->n *= -1.f;
				light_hit->mat = obj[i].material;
				if (obj[i].material.texture_id != -1 && !move_on)
				{
					uv = uv_mapping_for_sphere(light_hit);
					normalize_coord_for_texture(uv, &light_hit->mat.color, texture,  texture_param, obj[i].material.texture_id);
				}				
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
				// light_hit->hit += 0.00001f;		
				light_hit->n = obj[i].object.plane.axis;
				if (dot(d, light_hit->n) > 0.f)
				{
					// light_hit->hit -= 0.00002f;
					light_hit->n *= -1.f;
				}
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры	
				if (obj[i].material.texture_id != -1 && !move_on)
				{
					uv = uv_mapping_for_plane(light_hit);
					normalize_coord_for_texture(uv, &light_hit->mat.color, texture,  texture_param, obj[i].material.texture_id);
				}				
			}
		}
		else if (obj[i].type == o_cone)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cone(o, d, &(obj + i)->object.cone, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				v = normalize(light_hit->hit - obj[i].object.cone.center);
				light_hit->n = obj[i].object.cone.axis;
				light_hit->n = light_hit->n * ft_sign(dot(v, obj[i].object.cone.axis));
				light_hit->n = normalize(v * dot(v, light_hit->n) - light_hit->n);
				if (t12 == 2)
					light_hit->n *= -1;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
				if (obj[i].material.texture_id != -1 && !move_on)
				{
					uv = uv_mapping_for_cone(light_hit, &(obj + i)->object.cone);
					normalize_coord_for_texture(uv, &light_hit->mat.color, texture,  texture_param, obj[i].material.texture_id);
				}
			}
		}
		else if (obj[i].type == o_cylinder)
		{
			dist_i = 0.f;
			t12 = intersect_ray_cylinder(o, d, &(obj + i)->object.cylinder, &dist_i);
			if (t12 && dist_i < dist)
			{
				dist = dist_i;
				light_hit->hit = o + d * dist_i;
				v = light_hit->hit - obj[i].object.cylinder.center;
				light_hit->n = obj[i].object.cylinder.axis * dot(v, obj[i].object.cylinder.axis);
				light_hit->n = normalize(v - light_hit->n);
				if (t12 == 2)
					light_hit->n *= -1;
				light_hit->mat = obj[i].material;
				//условие для uv mapping и наличия текстуры
				if (obj[i].material.texture_id != -1 && !move_on)
				{
					uv = uv_mapping_for_cylinder(light_hit, &(obj + i)->object.cylinder);
					normalize_coord_for_texture(uv, &light_hit->mat.color, texture,  texture_param, obj[i].material.texture_id);
				}
			}
		}
		else if (obj[i].type == o_parab)
		{
			dist_i = 0.f;
			t12 = intersect_ray_parab(o, d, &(obj + i)->object.parab, &dist_i);
			if (t12 && dist_i < dist)
			{
				float	m;

				dist = dist_i;
				light_hit->hit = o + d * dist_i;				
				m = dot(light_hit->hit - obj[i].object.parab.center, obj[i].object.parab.axis);
				light_hit->n = normalize(light_hit->hit - obj[i].object.parab.center - obj[i].object.parab.axis * (m + obj[i].object.parab.k));
				if (t12 == 2)
					light_hit->n *= -1.f;
				light_hit->mat = obj[i].material;
				//uv mapping			
			}
		}
		i++;
	}
	return (dist < MAX_DIST);
}