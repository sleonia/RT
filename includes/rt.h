/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 04:06:50 by thorker           #+#    #+#             */
/*   Updated: 2020/01/27 04:06:52 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RT_H
# define RT_RT_H

# ifndef OPENCL___
#include "libft.h"
#include <SDL.h>
#include <math.h>
#include <OpenCL/opencl.h>
# define WIDTH 1280
# define HEIGHT 1024
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# endif

typedef struct			s_cylinder
{
# ifndef OPENCL___
	cl_float3			center;
	cl_float3			axis;
# else
	float3				center;
	float3				axis;
# endif
	float				radius;
	float				length;
}						t_cylinder;

typedef struct			s_plane
{
# ifndef OPENCL___
	cl_float3			axis;
# else
	float3				axis;
# endif
	float				dist;
}						t_plane;

typedef struct			s_cone
{
# ifndef OPENCL___
	cl_float3			center;
	cl_float3			axis;
# else
	float3				center;
	float3				axis;
# endif
	float				length;
	float				tan;
}						t_cone;

typedef struct			s_sphere
{
# ifndef OPENCL___
	cl_float3			center;
# else
	float3				center;
# endif
	float				radius;
}						t_sphere;

union					u_objects
{
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
	t_plane				plane;
};

typedef struct			s_material
{
# ifndef OPENCL___
	cl_float2			al;
	cl_float3			color;
# else
	float2				al;
	float3				color;
# endif
	float				sp_ex;
	float				refraction;
	float				reflection;
	int					specular;
	int					texture_id;
}						t_material;

typedef struct			s_cam
{
# ifndef OPENCL___
	cl_float3			pos;
	cl_float3			ox;
	cl_float3			oy;
	cl_float3			oz;
# else
	float3				pos;
	float3				ox;
	float3				oy;
	float3				oz;
# endif
	float				phi;
	float				tetta;
}						t_cam;

typedef struct 			s_light
{
# ifndef OPENCL___
	cl_float3			pos;
# else
	float3				pos;
# endif
	float 				intensity;
}						t_light;

enum					e_obj_type
{
	o_sphere = 1,
	o_cylinder,
	o_cone,
	o_plane,
};

typedef struct			s_object
{
	enum e_obj_type		type;
	t_material			material;
	union u_objects		object;
}						t_object;

typedef struct			s_scene
{
	t_light				*light;
	t_object			*object;
	t_cam				cam;
	int					count_objects;
	int					count_lights;
	int					*background;
	int					background_w;
	int					background_h;
}						t_scene;

typedef struct			s_cylinder_params
{
# ifndef OPENCL___
	cl_float3			pos;
	cl_float3			axis;
# else
	float3				pos;
	float3				axis;
# endif
	float				radius;
	int					color;
	int					specular;
	float				reflective;
}						t_cylinder_params;

typedef struct			s_cone_params
{
# ifndef OPENCL___
	cl_float3			pos;
	cl_float3			axis;
# else
	float3				pos;
	float3				axis;
# endif
	float				tan;
	int					color;
	int					specular;
	float				reflective;
}						t_cone_params;

typedef struct			s_plane_params
{
# ifndef OPENCL___
	cl_float3			pos;
	cl_float3			normal;
# else
	float3				pos;
	float3				normal;
# endif
	int					color;
	int					specular;
	float				reflective;
}						t_plane_params;

typedef struct			s_sphere_params
{
# ifndef OPENCL___
	cl_float3			pos;
# else
	float3				pos;
# endif
	float				radius;
	int					color;
	int					specular;
	float				reflective;
}						t_sphere_params;

# ifndef OPENCL___
typedef struct			s_cl
{
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_context			context;
	cl_uint				ret_num_devices;
	cl_command_queue	cmd_queue;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_work_size[2];
	size_t				local_work_size[2];
	cl_device_id		device_id;
	cl_mem				memobjs[6];
	char 				**program_source;
	size_t 				*program_size;
	size_t				count_files;
}						t_cl;

typedef struct 			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	SDL_Event			event;
	int					*pixels;
}						t_sdl;

typedef struct 			s_rt
{
	t_sdl				*sdl;
	t_cl				*opencl;
	t_scene				*scene;
}						t_rt;
# endif

# ifndef OPENCL___
int						sdl_init(t_sdl *sdl);
int						sdl_control(t_sdl *sdl, t_scene *scene, t_cl *cl);
void					init_light(t_light **light);
void					init_object(t_object **object);
void 					ft_error(char *str);
int						trace_start(t_sdl *sdl, t_scene *scene);
void                    func_error(int err);
int						read_kernel(t_cl *cl, char **files_cl);
int						create_cl(t_cl *cl, t_sdl *sdl, t_scene *scene);
int						set_arg(t_cl *cl, t_sdl *sdl, t_scene *scene);

void					calc_screen(t_cam *cam);
void					cl_to_norm(cl_float3 *v);
cl_float3				cl_mult_n(cl_float3 v1, float n);
float					cl_length(cl_float3 v);
cl_float3				cl_minus(cl_float3 v1, cl_float3 v2);
cl_float3				cl_sum(cl_float3 v1, cl_float3 v2);
cl_float3				cl_cross(cl_float3 v1, cl_float3 v2);
# endif
#endif
