#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

#include "libft/libft.h"
#include <SDL.h>
# define WIDTH 1920
# define HEIGHT 1080

typedef struct			s_pos
{
	double 				x;
	double 				y;
	double 				z;
}						t_pos;

typedef struct 			s_view
{
	t_pos				*position;
	//mb something else
}						t_view;

typedef struct 			s_cam
{
	t_pos				*position;
	//mb something else
}						t_cam;

typedef struct 			s_light
{
	t_pos				*position;
	double 				brightness;
	struct s_light		*next;
	//mb something else
}						t_light;

typedef struct 			s_fig
{
	t_pos				*position;
	int 				color;
	char 				type;
	struct s_fig		*next;
	//mb something else
}						t_fig;

typedef struct 			s_scene
{
	t_view				*view;
	t_cam				*cam;
	t_light				*light;
	t_fig				*figure;
	//mb something else
}						t_scene;

/*typedef struct		s_cl
{
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_context			context;
	cl_uint				ret_num_devices;
	cl_command_queue	cmd_queue;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_work_size[1];
	cl_device_id		device_id;
	cl_mem				memobjs;
	char 				*program_source;
	size_t 				program_size;
}						t_cl;*/

typedef struct 			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	SDL_Event			event;
	int					*pixels;
	//mb something else
}						t_sdl;

typedef struct 			s_rtv1
{
	t_sdl				*sdl;
//	t_sl				*opencl;
	t_scene				*scene;
	//mb something else
}						t_rtv1;


#endif
