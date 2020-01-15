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

	if ((fabsf(v.z) < 0.00001f))
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
	if ((*cam).b > 0.00001f)
		v[1] = cl_mult_n(v[1], (-1));
	v[0] = cl_cross(v[2], v[1]);
	cl_to_norm(&v[0]);
	cl_to_norm(&v[1]);
	(*cam).v1 = v[0];
	(*cam).v2 = v[1];
	(*cam).center = v[2];
	// printf("v1 = %f %f %f\n", v[0].x, v[0].y, v[0].z);
	// printf("v2 = %f %f %f\n", v[1].x, v[1].y, v[1].z);
	// printf("center = %f %f %f\n", v[2].x, v[2].y, v[2].z);
}