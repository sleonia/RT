#include <rtv1.h>
#include "./includes/kernel.h"

__kernel void RT(__global int *arr, t_object *obj, t_light *light)
{
	int 	color;
	int 	x;
	int 	y;
	int		pixel;

	pixel = get_global_id(0);
	x = pixel / HEIGHT % WIDTH - WIDTH / 2;
	y = HEIGHT /2 - pixel / WIDTH;
	scene->view = matrix_on_vector(scene->cam->a, scene->cam->b, canvas_to_viewport(x, y, scene->view));
	color = trace_ray(&scene->cam->position, scene->view, 1.0, INFINITY, scene, 3);
	arr = put_pixel(x, y, color, sdl);
}