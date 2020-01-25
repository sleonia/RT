
#include "./includes/kernel.h"
#include "./includes/rt.h"

float3	uv_mapping_for_skybox(__global int *skybox, float3 d, int tex_width, int tex_height)
{
	float3	vec;
	float 	v;
	float 	u;
	int		coord;

	vec = -d;
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f + (asin(vec.y) / M_PI_F);
	coord = (int)(u * tex_width) + (int)(v * tex_height) * tex_width;
	// coord += prev_texture_size[screen->skybox_id];
	return ((float3){(RED(skybox[coord]) * 0.00392156862f), (GREEN(skybox[coord]) * 0.00392156862f), (BLUE(skybox[coord]) * 0.00392156862f)});
}