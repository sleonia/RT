/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:18:10 by deladia           #+#    #+#             */
/*   Updated: 2019/10/25 21:18:13 by deladia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

#include "libft/libft.h"
#include <SDL.h>
#include <OpenCL/opencl.h>
#include <math.h>
# define WIDTH 1280
# define HEIGHT 1024
# define VW 1.25
# define VH 1
# define D 1
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct			s_result
{
	double 				t1;
	double 				t2;
}						t_result;

typedef struct			s_pos
{
	double 				x;
	double 				y;
	double 				z;
}						t_pos;

typedef struct 			s_light
{
	char 				type;
	double 				intensity;
	t_pos				*position;
	struct s_light		*next;
	//mb something else
}						t_light;

typedef struct 			s_cylinder
{
	t_pos				*center;
	double 				height;
	int 				color;
	double				radius;
	int 				specular;
	double				reflective;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct 			s_cone
{
	t_pos				*center;
//	double 				height;
	int 				color;
//	double				radius;
	int 				specular;
	double				reflective;
	struct s_cone		*next;
}						t_cone;

typedef struct 			s_plane
{
//	t_pos				*center;
//	double 				height;
	int 				color;
//	double				radius;
	int 				specular;
	double				reflective;
	struct s_plane		*next;
}						t_plane;

typedef struct 			s_sphere
{
	t_pos				*center;
	int 				color;
	double				radius;
	int 				specular;
	double				reflective;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_return
{
	t_sphere			*closest_sphere;
	double				closest_t;
}						t_return;

typedef struct			s_figure
{
	t_cylinder			*cylinder;
	t_sphere			*sphere;
	t_cone				*cone;
	t_plane				*plane;
}						t_figure;

typedef struct			s_cam
{
	t_pos				*position;
	t_pos				*cam_rotation;
}						t_cam;

typedef struct 			s_scene
{
	t_pos				*view;
	t_cam				*cam;
	t_light				*light;
	t_figure			*figure;
	//mb something else
}						t_scene;

typedef struct		s_cl
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
}						t_cl;

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
	t_cl				*opencl;
	t_scene				*scene;
	//mb something else
}						t_rtv1;

t_pos					*insert(int x,int y, int z, t_pos *pos);
t_pos					*canvas_to_viewport(int x, int y, t_pos *pos);
t_pos					vector_minus(t_pos *o, t_pos	*center);
double 					dot(t_pos *a, t_pos *b);
int						sdl_init(t_sdl *sdl);
int						sdl_control(t_sdl *sdl, t_scene *scene);
int						*put_pixel(double x, double y, int color, t_sdl *sdl);
t_pos					vector_pus(t_pos *o, t_pos *center);
t_pos					vector_on_number(t_pos *o, double nbr);
t_pos					vector_div(t_pos *o, double nbr);
double					vector_len(t_pos *o);
double					computer_lighting(t_pos *p, t_pos *n, t_pos *v, int s, t_scene *scene);
t_light					*init_light(t_light *light);
void 					ft_error(char *str);
t_return				closest_intersection(t_pos *o, t_pos *d, double t_min, double t_max, t_sphere *sphere);
int						trace_start(t_sdl *sdl, t_scene *scene);
t_pos					*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab);

#endif
