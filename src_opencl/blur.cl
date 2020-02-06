
#include "./includes/kernel.h"
#include "./includes/rt.h"

static float	coef(int x, int sigma)
{
	return(1.f / (sqrt(2 * M_PI_F) * sigma) * exp(-(float)(x * x) / (2 * sigma * sigma)));
}

static float3	color_vec(int color)
{
	float3		vector;

	vector.x = RED(color) * 0.00392156862f;
	vector.y = GREEN(color) * 0.00392156862f;
	vector.z = BLUE(color) * 0.00392156862f;
	return (vector);
}

__kernel void	blur_x(__global int *input_pixels, __global int *output_pixels)
{
	int			x;
	int			y;
	int			pixel;
	int			sigma = 4;
	float3		color = (float3)0;
	float		sum = 0;
	float		coeff;
	int			a;

	x = get_global_id(0);
	y = get_global_id(1);
	pixel = y * WIDTH + x;
	a = 3 * sigma;
	for (int i = -a; i <= a; i++)
	{
		if (x + i >= 0 && x + i < WIDTH)
		{
			coeff = coef(i, sigma);
			sum += coeff;
			color += color_vec(input_pixels[WIDTH * y + (x + i)]) * coeff;
		}
	}
	output_pixels[pixel] = get_color(color / sum);
}

__kernel void	blur_y(__global int *input_pixels, __global int *output_pixels)
{
	int			x;
	int			y;
	int			pixel;
	int			sigma = 4;
	float3		color = (float3) 0;
	float		sum = 0;
	float		coeff;
	int			a;

	x = get_global_id(0);
	y = get_global_id(1);
	pixel = y * WIDTH + x;
	a = 3 * sigma;
	for (int i = -a; i <= a; i++)
	{
		if (y + i >= 0 && y + i < HEIGHT)
		{
			coeff = coef(i, sigma);
			sum += coeff;
			color += color_vec(input_pixels[WIDTH * (y + i) + x]) * coeff;
		}
	}
	output_pixels[pixel] = get_color(color / sum);
}
