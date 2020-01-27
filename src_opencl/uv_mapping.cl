
#include "./includes/kernel.h"
#include "./includes/rt.h"

float3	uv_mapping_for_skybox(__global int *skybox, float3 d, __global int *tex_param, const int text_id)
{
	float3	vec;
	float 	v;
	float 	u;
	int		coord;
	int		tex_width;
	int		tex_height;

	vec = -d;
	tex_width = tex_param[text_id * 3 + 1];
	tex_height = tex_param[text_id * 3 + 2];
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f + (asin(vec.y) / M_PI_F);
	coord = (int)(u * tex_width) + (int)(v * tex_height) * tex_width;
	coord += tex_param[text_id * 3];
	return ((float3){(RED(skybox[coord]) * 0.00392156862f), (GREEN(skybox[coord]) * 0.00392156862f), (BLUE(skybox[coord]) * 0.00392156862f)});
}