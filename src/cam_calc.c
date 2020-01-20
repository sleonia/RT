#include "rtv1.h"

cl_float3	spherical_coor(float phi, float tetta)
{
	cl_float3	vec;

	vec.s[0] = sinf(tetta) * cosf(phi);
	vec.s[2] = sinf(tetta) * sinf(phi);
	vec.s[1] = cosf(tetta);
	return (vec);
}

cl_float3	spher_norm(cl_float3 vec)
{
	cl_float3	normal;

	if ((fabsf(vec.s[2]) < 0.00001f))
	{
		normal.s[0] = 0.f;
		normal.s[1] = -1.f;
		normal.s[2] = 0.f;
	}
	else
	{
		normal.s[0] = vec.s[0];
		normal.s[1] = -(vec.s[0] * vec.s[0] + vec.s[2] * vec.s[2]) / vec.s[1];
		normal.s[2] = vec.s[2];
	}
	return (normal);
}

void		calc_screen(t_cam *cam)
{
	cl_float3	dec_coor;
	cl_float3	v1;
	cl_float3	v2;
	cl_float3	center;

	if ((*cam).tetta == 0.0f)
		(*cam).tetta = 0.0001;
	dec_coor = spherical_coor((*cam).phi, (*cam).tetta);
	dec_coor = cl_sum(dec_coor, (*cam).pos);
	center = cl_minus((*cam).pos, dec_coor);
	v2 = spher_norm(center);
	if ((*cam).tetta > (float)M_PI_2 - 0.00001f)
		v2 = cl_mult_n(v2, (-1));
	v1 = cl_cross(center, v2);
	cl_to_norm(&v1);
	cl_to_norm(&v2);
	(*cam).v1 = v1;
	(*cam).v2 = v2;
	(*cam).center = center;
	// printf("v1 = %f %f %f\n", v1.x, v1.y, v1.z);
	// printf("v2 = %f %f %f\n", v2.x, v2.y, v2.z);
	// printf("center = %f %f %f\n", center.x, center.y, center.z);
}