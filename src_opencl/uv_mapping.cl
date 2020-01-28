
#include "./includes/kernel.h"
#include "./includes/rt.h"

static float3			vec_change(t_hitting *lighting, __global t_object *obj)
{
    float3	n;
    float3	vec;
    float	cos_x,		cos_z;
    float3	new_vec,	new_n;
    float	alpha_x,	alpha_z;

	if (obj->type == o_cylinder)
	{
		n = obj->object.cylinder.axis;
		vec = obj->object.cylinder.center;
	}
	else if (obj->type == o_cone)
	{
		n = obj->object.cylinder.axis;
		vec = obj->object.cylinder.center;
	}
    if (length((float2)(n.x, n.y)) < 1e-5f)
        return (vec);
    else
    {
        cos_x = n.x / length((float2)(n.x, n.y));
        if (n.y > 0.f)
            alpha_x = acos(cos_x);
        else
            alpha_x = -acos(cos_x);
    }

    float cos_alpha_x = cos(alpha_x);
	float sin_alpha_x = sin(alpha_x);
    new_vec.x = dot((float3)(cos_alpha_x, sin_alpha_x, 0.f), vec);
    new_vec.y = dot((float3)(-sin_alpha_x, cos_alpha_x, 0.f), vec);
    new_vec.z = dot((float3)(0.f, 0.f, 1.f), vec);

    new_n.x = dot((float3)(cos_alpha_x, sin_alpha_x, 0.f), n);
    new_n.y = dot((float3)(-sin_alpha_x, cos_alpha_x, 0.f), n);
    new_n.z = dot((float3)(0.f, 0.f, 1.f), n);


    cos_z = new_n.z / length(new_n);
    if (new_n.x > 0)
        alpha_z = acos(cos_z);
    else
        alpha_z = -acos(cos_z);

	float cos_alpha_z = cos(alpha_z);
	float sin_alpha_z = sin(alpha_z);
    vec.x = dot((float3)(cos_alpha_z, 0.f, -sin_alpha_z), new_vec);
    vec.y = dot((float3)(0.f, 1.f, 0.f), new_vec);
    vec.z = dot((float3)(sin_alpha_z, 0.f, cos_alpha_z), new_vec);

    return (vec);
}

void	normalize_coord_for_texture(float2 uv, float3 *color, __global int *texture,  __global int *texture_param, int texture_id)
{
	int	coord;
	int		tex_width;
	int		tex_height;

	tex_width = texture_param[texture_id * 3 + 1];
	tex_height = texture_param[texture_id * 3 + 2];
	coord = (int)(uv.x * tex_width) + (int)(uv.y * tex_height) * tex_width;
	coord += texture_param[texture_id * 3];

	color->x = (RED(texture[coord])) * 0.00392156862f;
	color->y = (GREEN(texture[coord])) * 0.00392156862f;
	color->z = (BLUE(texture[coord])) * 0.00392156862f;
}

float3	uv_mapping_for_skybox(__global int *texture, float3 d, __global int *tex_param, const int text_id)
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
	return ((float3){(RED(texture[coord]) * 0.00392156862f), (GREEN(texture[coord]) * 0.00392156862f), (BLUE(texture[coord]) * 0.00392156862f)});
}

float2			uv_mapping_for_sphere(t_hitting *light_hit)
{
	float3	vec;
	float 	v;
	float 	u;

	vec = light_hit->n;
	u = 0.5f + (atan2(vec.x, vec.z) / (2.f * M_PI_F));
	v = 0.5f - (asin(vec.y) / M_PI_F);
	return ((float2){u, v});
}

float2			uv_mapping_for_plane(t_hitting *light_hit)
{
	float3 vec;
	float3 normvec;
	float3 crossvec;
	float v;
	float u;

    vec = light_hit->hit;

	if (light_hit->n.x != 0.0f || light_hit->n.y != 0.0f)
		normvec = normalize((float3) {light_hit->n.y, -light_hit->n.x, 0.0f});
	else
		normvec = (float3) {0.0f, 1.0f, 0.0f};

	crossvec = cross(light_hit->n, normvec);
	u = 0.5f + fmod(dot(normvec, vec), 16.0f) / 32.f;
	v = 0.5f + fmod(dot(crossvec, vec), 16.0f) / 32.f;
	return ((float2){u, v});
}

float2			uv_mapping_for_cylinder(t_hitting *light_hit, __global t_object *obj)
{
	float3	vec;
	float 	v;
	float 	u;

	vec = vec_change(light_hit, obj);
	u = 0.5f + (atan2(vec.x, vec.y) / (2.f * M_PI_F));
    v = 0.5f - (modf(vec.z / obj->object.cylinder.radius * 250.f / 1024.f, &v) / 2.f);
	return ((float2){u, v});
}