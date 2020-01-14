#include "rtv1.h"

cl_float3	spherical(float phi, float tetta)
{
	cl_float3	v;

	v.x = sinf(tetta) * cosf(phi);
	v.y = sinf(tetta) * sinf(phi);
	v.z = cosf(tetta);
	return (v);
}

cl_float3	spher_norm(cl_float3 v)
{
	cl_float3	n;

	if ((fabsf(v.z) < 1e-5f))
	{
		n.x = 0.f;
		n.y = 0.f;
		n.z = -1.f;
	}
	else
	{
		n.x = v.x;
		n.y = v.y;
		n.z = -(v.x * v.x + v.y * v.y) / v.z;
	}
	return (n);
}

void		calc_screen(t_cam *cam)
{
	cl_float3	check;
	cl_float3	v[3];

	check = spherical((*cam).a, (*cam).b);
	check = cl_sum(check, (*cam).pos);
	v[2] = cl_minus((*cam).pos, check);
	v[1] = spher_norm(v[2]);
	if ((*cam).b > (float)M_PI_2 - 0.00001f)
		v[1] = cl_mult_n(v[1], (-1));
	v[0] = cl_cross(v[2], v[1]);
	cl_to_norm(&v[0]);
	cl_to_norm(&v[1]);
	(*cam).v1 = v[0];
	(*cam).v2 = v[1];
	(*cam).center = v[2];
}