#include "./includes/rtv1.h"



static int 		color_scale(int	color, double c)
{
	int 	red;
	int 	green;
	int 	blue;

	red = (color & 0xFF0000) >> 16;
	red = (int)((double)red * c);
	green = (color & 0x00FF00) >> 8;
	green = (int)((double)green * c);
	blue = (color & 0x0000FF);
	blue = (int)((double)blue * c);
	return ((red << 16) | (green << 8) | blue);
}



static t_pos		*canvas_to_viewport(int x, int y, t_pos *pos)
{
	pos->x = (double)x * VW / WIDTH;
	pos->y = (double)y * VH / HEIGHT;
	pos->z = D;
	return (pos);
}

static t_pos		vector_on_number(t_pos *o, double nbr)
{
	t_pos	oc;

	oc.x = o->x * nbr;
	oc.y = o->y * nbr;
	oc.z = o->z * nbr;
	return (oc);
}

static t_pos		vector_div(t_pos *o, double nbr)
{
	t_pos	oc;

	oc.x = o->x / nbr;
	oc.y = o->y / nbr;
	oc.z = o->z / nbr;
	return (oc);
}

static double		vector_len(t_pos *o)
{
	return(sqrt(o->x * o->x + o->y * o->y + o->z * o->z));
}

static t_pos		vector_minus(t_pos *o, t_pos *center)
{
	t_pos	oc;

	oc.x = o->x - center->x;
	oc.y = o->y - center->y;
	oc.z = o->z - center->z;
	return (oc);
}

static t_pos		vector_pus(t_pos *o, t_pos *center)
{
	t_pos	oc;

	oc.x = o->x + center->x;
	oc.y = o->y + center->y;
	oc.z = o->z + center->z;
	return (oc);
}

static t_pos		*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab)
{
	ab->x = a->x * b->x;
	ab->y = a->y * b->y;
	ab->z = a->z * b->z;
	return (ab);
}

static t_pos		*my_matrix_on_vector(double a, double b, t_pos *vec)
{
	double	x;
	double	y;
	double	z;

	x = vec->x;
	y = vec->y;
	z = vec->z;
	vec->x = x * cos(b) + z * sin(b);
	vec->y = (x * sin(b) - z * cos(b)) * sin(a) + y * cos(a);
	vec->z = (z * cos(b) - x * sin(b)) + y * sin(a);
	return (vec);
}

static double		ft_dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

static t_pos		v_plus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

static t_pos		v_minus(t_pos v1, t_pos v2)
{
	t_pos	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return (new_v);
}

static t_pos	get_cone_normal(t_pos *start_ray, t_pos *ray, t_cone *obj, double intersect_dist)
{
	t_pos	ret_normal;
	t_pos	oc;
	double	m;

	oc = vector_minus(start_ray, &obj->center);
	m = ft_dot(ray, &obj->axis) * intersect_dist + ft_dot(&oc, &obj->axis);
	ret_normal = v_minus(v_plus(vector_on_number(ray, intersect_dist), oc), vector_on_number(&obj->axis, (1 + obj->tan * obj->tan) * m));
	return (ret_normal);
}

static t_pos	get_cylinder_normal(t_cylinder *obj, t_pos *intersect_point)
{
	t_pos	n;
	t_pos	v;

	v = vector_minus(intersect_point, &obj->center);
	n = vector_on_number(&obj->axis, ft_dot(&v, &obj->axis));
	n = vector_minus(&v, &n);
	return (n);
}

static t_pos	get_obj_normal(t_pos *p, t_return *ret, t_pos *o, t_pos *d)
{
	t_pos		n;
	t_object	*obj;

	obj = ret->closest_object;
	if (obj->type == o_sphere)
		n = vector_minus(p, &obj->objects->sphere.center);
	else if (obj->type == o_plane)
		n = obj->objects->plane.normal;
	else if (obj->type == o_cone)
		n = get_cone_normal(o, d, &obj->objects->cone, ret->closest_t);
	else if (obj->type == o_cylinder)
		n = get_cylinder_normal(&obj->objects->cylinder, p);
	n = vector_div(&n, vector_len(&n));
	return (n);
}

static t_result	intersect_ray_sphere(t_pos *o, t_pos *d, t_sphere *sphere)
{
	t_pos		oc;
	double		k1;
	double		k2;
	double		k3;
	t_result	res;


	oc = vector_minus(o, &sphere->center);
	k1 = ft_dot(d, d);
	k2 = 2 * ft_dot(&oc, d);
	k3 = ft_dot(&oc, &oc) - sphere->radius * sphere->radius;
	if (k2 * k2 - 4 * k1 * k3 < 0)
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
		return (res);
	}
	res.t1 = (-k2 + sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	res.t2 = (-k2 - sqrt(k2 * k2 - 4 * k1 * k3)) / (2 * k1);
	return (res);
}

static t_result    intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cyl)
{
	t_result    res;
	t_pos oc;
	double  a;
	double  b;
	double  c;
	double  discr;

	oc = vector_minus(o, &cyl->center);
	a = ft_dot(d,d) - ft_dot(d,&cyl->axis) * ft_dot(d,&cyl->axis);
	c = ft_dot(&oc,&oc) - ft_dot(&oc,&cyl->axis) * ft_dot(&oc,&cyl->axis) - cyl->radius * cyl->radius;
	b = ft_dot(d,&oc) - ft_dot(d,&cyl->axis) * ft_dot(&oc,&cyl->axis);
	discr = b*b - a*c;
	if (discr < 0.0 )
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
	}
	else
	{
		res.t1 = (-b - sqrt(discr))/(a);
		res.t2 = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static t_result intersect_ray_plane(t_pos *cam, t_pos *view, t_plane *pl)
{
	double  t;
	t_pos   oc;
	t_pos   min;
	t_result res;

	oc = vector_minus(cam,&pl->center);
	min = vector_on_number(&oc,-1);
	t = ft_dot(&min,&pl->normal) / ft_dot(view,&pl->normal);
	res.t1 = t;
	res.t2 = INFINITY;
	return (res);
}

static t_result    intersect_ray_cone(t_pos *o, t_pos *d, t_cone *cone)
{
	t_result    res;
	t_pos oc;
	double  a;
	double  b;
	double  c;
	double  discr;

	oc = vector_minus(o, &cone->center);
	a = ft_dot(d,d) - (1 + cone->tan * cone->tan)*ft_dot(d,&cone->axis) * ft_dot(d,&cone->axis);
	c = ft_dot(&oc,&oc) - (1 + cone->tan * cone->tan)*ft_dot(&oc,&cone->axis) * ft_dot(&oc,&cone->axis);
	b = ft_dot(d,&oc) - (1 + cone->tan * cone->tan)*ft_dot(d,&cone->axis) * ft_dot(&oc,&cone->axis);
	discr = b*b - a*c;
	if (discr < 0.0 )
	{
		res.t1 = INFINITY;
		res.t2 = INFINITY;
	}
	else
	{
		res.t1 = (-b - sqrt(discr))/(a);
		res.t2 = (-b + sqrt(discr))/(a);
	}
	return (res);
}

static t_result	get_intersect(t_pos *o, t_pos *d, t_object *obj)
{
	if (obj->type == o_sphere)
		return (intersect_ray_sphere(o, d, &obj->objects->sphere));
	else if (obj->type == o_plane)
		return (intersect_ray_plane(o, d, &obj->objects->plane));
	else if (obj->type == o_cone)
		return (intersect_ray_cone(o, d, &obj->objects->cone));
	else
		return (intersect_ray_cylinder(o, d, &obj->objects->cylinder));
}

static t_return	closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_object **obj)
{
	t_result	res;
	t_object	**tmp;
	t_return	ret;
	int 		i;

	ret.closest_t = INFINITY;
	ret.closest_object = 0;
	tmp = obj;
	i = 0;
	while (i < 7)
	{
		res = get_intersect(o, d, tmp[i]);
		if (res.t1 >= t_min && res.t1 <= t_max && res.t1 < ret.closest_t)
		{
			ret.closest_t = res.t1;
			ret.closest_object = tmp[i];
		}
		if (res.t2 >= t_min && res.t2 <= t_max && res.t2 < ret.closest_t)
		{
			ret.closest_t = res.t2;
			ret.closest_object = tmp[i];
		}
		i++;
	}
	return (ret);
}

static double		computer_lighting(t_pos *p, t_pos *n, t_pos *v, int specular, __global t_scene *scene)
{
	double		intens;
	t_light		**tmp;
	t_pos		l;
	double		n_dot_l;
	double		r_dot_v;
	t_pos		r;
	t_pos		buf;
	t_return	shadow;
	double		t_max;
	int 		i;

	i = 0;
	intens = 0.0;
	tmp = scene->light;
	l = vector_on_number(&l, 0);
	while (i < 3)
	{
		if (tmp[i]->type == 'A' && !scene->off->ambient)
			intens += tmp[i]->intensity;
		else
		{
			if (tmp[i]->type == 'P' && !scene->off->point)
			{
				l = vector_minus(&tmp[i]->position, p);
				t_max = 1.0;
			}
			else if (tmp[i]->type == 'D' && !scene->off->directional)
			{
				l.x = tmp[i]->position.x;
				l.y = tmp[i]->position.y;
				l.z = tmp[i]->position.z;
				t_max = INFINITY;
			}
			if (t_max)
			{
				shadow = closest_intersection(p, &l, 0.001, t_max, scene->object);
				if (shadow.closest_object != 0)
				{
					i++;
					continue ;
				}
				n_dot_l = ft_dot(n, &l);
				if (n_dot_l > 0)
					intens += tmp[i]->intensity * n_dot_l / (vector_len(n) * vector_len(&l));
				if (specular != -1)
				{
					buf = vector_on_number(n, 2);
					buf = vector_on_number(&buf, ft_dot(n, &l));
					r = vector_minus(&buf, &l);
					r_dot_v = ft_dot(&r, v);
					if (r_dot_v > 0)
						intens += tmp[i]->intensity * pow(r_dot_v / (vector_len(&r) * vector_len(v)), specular);
				}
			}
		}
		i++;
	}
	if (intens > 1.0)
		return (1.0);
	return (intens);
}

static int			 my_trace_ray(t_pos *o, t_pos *d, double t_min, double t_max, __global t_scene *scene)
{
	t_pos p;
	t_pos n;
	t_pos buf;
	t_return ret;
	double c;
	int local_color;

	ret = closest_intersection(o, d, t_min, t_max, scene->object);
	if (ret.closest_object == 0)
		return (BLACK);
	buf = vector_on_number(d, ret.closest_t);
	p = vector_pus(o, &buf);
	n = get_obj_normal(&p, &ret, o, d);
	n = vector_div(&n, vector_len(&n));
	buf = vector_on_number(d, -1);
	c = computer_lighting(&p, &n, &buf, ret.closest_object->specular, scene);
	local_color = color_scale(ret.closest_object->color, c);
	return (local_color);
}

__kernel void RT(__global int *arr, __global t_scene *scene)
{
	int 	color;
	int 	x;
	int 	y;
	int		pixel;

	pixel = get_global_id(0);
	x = pixel / HEIGHT % WIDTH - WIDTH / 2;
	y = HEIGHT /2 - pixel / WIDTH;
	scene->view = my_matrix_on_vector(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y, scene->view));
	color = my_trace_ray(&scene->cam->position, scene->view, 1.0, INFINITY, scene);
	arr[pixel] = color;
}