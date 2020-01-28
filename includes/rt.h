/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 04:06:50 by thorker           #+#    #+#             */
/*   Updated: 2020/01/28 19:55:34 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RT_H
# define RT_RT_H

# ifndef OPENCL___
# include "libft.h"
# include "rt_error.h"
# include <SDL.h>
# include "audio.h"
# include "to_json.h"
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <stdbool.h>
# include <math.h>
# include <time.h>
# include <OpenCL/opencl.h>
# define WIDTH 1280
# define HEIGHT 1024
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define STEP 0.1
# define MAX_NBR_OF_SONGS 20
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
	cl_float3			color;
# else
	float3				color;
# endif
	float				ambient;
	float				diffuse;
	float				specular; //от 0 до 100
	float				refraction;
	float				reflection;
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
	int					skybox_id;	
	int					*texture;
	int					*texture_param;
	int					texture_length;
	int					texture_cnt;
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
	char				**files;
}						t_cl;

typedef struct 			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	Mix_Music			*music[MAX_NBR_OF_SONGS];
	SDL_Event			event;
	int					*pixels;
	int					volume;
	
}						t_sdl;

typedef struct 			s_rt
{
	t_sdl				*sdl;
	t_cl				*opencl;
	t_scene				*scene;
	t_key_value			*json;
}						t_rt;
# endif

# ifndef OPENCL___

/*
**						hooks
*/
void					events_processing(char *quit, t_sdl *sdl,
								t_scene *scene, t_cl *cl);
void					key_events(char *quit, t_sdl *sdl,
								t_scene *scene, t_cl *cl);
void					mouse_events(char *quit, t_sdl *sdl,
								t_scene *scene, t_cl *cl);
void					move(SDL_Event event, t_sdl *sdl, t_cam *cam);
void					rotation(SDL_Event event, t_sdl *sdl, t_cam *cam);

/*
**						init
*/
char					**init_files_cl(void);
void					init_light(t_light **light);
int						set_opencl_arg(t_cl *cl, t_sdl *sdl, t_scene *scene);
int						create_cl(t_cl *cl, t_sdl *sdl, t_scene *scene);
t_rt					*init_rt(char **av);
t_sdl					*init_sdl(t_key_value *json);
int						*fill_texture_for_object(char *texture_path,
											int *texture_pixels,
											int *texture_param);

/*
**						math_utils
*/
cl_float3				spherical_coor(float phi, float tetta);
cl_float3				spher_norm(cl_float3 vec);
void					calc_screen(t_cam *cam);
cl_float3				cl_mult_n(cl_float3 v1, float n);
void					cl_to_norm(cl_float3 *v);
cl_float3				cl_cross(cl_float3 v1, cl_float3 v2);
cl_float3				cl_sum(cl_float3 v1, cl_float3 v2);
cl_float3				cl_minus(cl_float3 v1, cl_float3 v2);
float					cl_length(cl_float3 v);

/*
** t_pos					vector_minus(t_pos *o, t_pos *center);
** t_pos					vector_pus(t_pos *o, t_pos *center);
** t_pos					*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab);
** t_pos					*matrix_on_vector(double a, double b, t_pos *vec);
** double					ft_dot(t_pos *a, t_pos *b);
** t_pos					v_plus(t_pos v1, t_pos v2);
** t_pos					v_minus(t_pos v1, t_pos v2);
** t_pos					*insert(int x, int y, int z, t_pos *pos);
** t_pos					vector_on_number(t_pos *o, double nbr);
** t_pos					vector_div(t_pos *o, double nbr);
** double					vector_len(t_pos *o);
*/

/*
**						parse
*/
void					parse_songs_json(t_key_value *assets, t_sdl *sdl);
int						parse_volume_json(t_key_value *assets);
char					*parse_textures_json(t_key_value *assets, t_sdl *sdl);
char					*parse_icon_json(t_key_value *assets, t_sdl *sdl);
t_key_value				*parse_assets(t_key_value *json, t_sdl *sdl);
/*
**						sdl_utils
*/
void					change_music(t_rt *rt);
void					sdl_loop(t_sdl *sdl, t_scene *scene, t_cl *cl);
void					sdl_quit(t_sdl *sdl);
void 					sdl_update(t_sdl *sdl);

/*
**						utils
*/
void					ft_error(char *str);
char					*get_next_name(char *name);
cl_int3					int_to_rgb(int src_color);
int 					*put_pixel(double x, double y, int color, t_sdl *sdl);
int						read_kernel(t_cl *cl, char **files_cl);
int						realloc_img(t_scene *scene, char *file_name);

# endif
#endif
