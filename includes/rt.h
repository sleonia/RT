/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 04:06:50 by thorker           #+#    #+#             */
/*   Updated: 2020/02/05 19:24:40 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_RT_H
# define RT_RT_H

# ifndef OPENCL___
#  include "libft.h"
#  include "to_json.h"
#  include "rt_error.h"
#  include <SDL.h>
#  include <SDL_image.h>
#  include <SDL_mixer.h>
#  include <SDL_ttf.h>
#  include "../Simple-SDL2-Audio/audio.h"
#  include <math.h>
#  include <time.h>
#  include <OpenCL/opencl.h>
#  include "audio.h"
#  include <stdbool.h>
#  define STEP 0.1
#  define NEGATIVE -101
#  define SEPIA -102
#  define NBR_OF_SONGS	20
#  define DISPLAY_NOT	"osascript -e \'display notification\""
#  define MIN(a,b) (((a)<(b))?(a):(b))
#  define MAX(a,b) (((a)>(b))?(a):(b))
#  define FONT			"assets/fonts/open-sans/OpenSans-Regular.ttf"
# endif
# define WIDTH 1280
# define HEIGHT 1024
# define MAX_DIST 10000.f
# define RED(color) (((int)color >> 16) & 0xFF)
# define GREEN(color) (((int)color >> 8) & 0xFF)
# define BLUE(color) ((int)color & 0xFF)

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
	float				specular;
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

typedef struct			s_light
{
# ifndef OPENCL___

	cl_float3			pos;
# else

	float3				pos;
# endif

	float				intensity;
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
	float				ambient;
	int					fsaa;
	int					move_on;
}						t_scene;

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
	char				**program_source;
	size_t				*program_size;
	size_t				count_files;
	char				**files;
}						t_cl;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	Mix_Music			*music[NBR_OF_SONGS];
	char				*sounds[NBR_OF_SONGS];
	SDL_Event			event;
	int					*pixels;
	SDL_Surface			*sur;
	int					volume;
	bool				help_screen_flag;
	TTF_Font			*font;
	int					font_size;
	SDL_Color			font_color;
}						t_sdl;

typedef struct			s_rt
{
	t_sdl				*sdl;
	t_cl				*opencl;
	t_scene				*scene;
}						t_rt;
# endif

# ifndef OPENCL___

/*
**						hooks
*/

void					events_processing(char *quit, t_object **hi_lited_object, t_rt *rt);
int						key_events(char *quit, t_object *hi_lited_object,
								t_rt *rt);
int						mouse_events(char *quit,t_sdl *sdl,
								t_object **hi_lited_object, t_scene *scene);
void					move(SDL_Event event, t_cam *cam);
void					rotation(SDL_Event event, t_sdl *sdl, t_cam *cam);
t_object				*get_object(t_scene *scene, int x, int y);

/*
**						init
*/

char					**init_cl_files(void);
void					create_cl(t_cl *cl, t_sdl *sdl, t_scene *scene);
void					init_light(t_light **light, int nbr);
void					init_objects(t_object **object, int nbr);
int						set_opencl_arg(t_cl *cl, t_sdl *sdl, t_scene *scene);
t_cl					*init_cl(t_rt *rt);
t_rt					*init_rt(char **av);
t_scene					*init_scene(t_key_value *json, char *sounds[]);
t_sdl					*init_sdl(t_key_value *json);
void					print_build_error(t_cl *cl, cl_int ret, size_t log_size);
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
void					cl_normalize(cl_float3 *v);
cl_float3				cl_cross(cl_float3 v1, cl_float3 v2);
cl_float3				cl_sum(cl_float3 v1, cl_float3 v2);
cl_float3				cl_minus(cl_float3 v1, cl_float3 v2);
float					cl_length(cl_float3 v);
float					dot(cl_float3 a, cl_float3 b);

/*
**						parse
*/

void					parse_sounds_json(t_key_value *assets, t_sdl *sdl);
void					parse_music_json(t_key_value *assets, t_sdl *sdl);
void					parse_array_of_float(t_array *array, cl_float3 *pos);
int						parse_volume_json(t_key_value *assets);
void					parse_texture(t_key_value *json, t_scene *scene,
										char *sounds[]);
char					*parse_icon_json(t_key_value *assets, t_sdl *sdl);
t_key_value				*parse_assets(t_key_value *json, t_sdl *sdl);

void					parse_cam_json(t_key_value *json,
										t_scene *scene, char *sounds[]);
void					parse_light_json(t_key_value *json,
										t_scene *scene, char *sounds[]);
void					parse_material_json(t_key_value *obj, t_object *object,
										int texture_cnt, char *sounds[]);
void					parse_objects_json(t_key_value *json,
										t_scene *scene, char *sounds[]);
void					parse_skybox_json(t_key_value *json,
										t_scene *scene, char *sounds[]);

void					parse_sphere_json(t_key_value *obj, t_sphere *sphere);
void					parse_plane_json(t_key_value *obj, t_plane *plane);
void					parse_cone_json(t_key_value *obj, t_cone *cone);
void					parse_cylinder_json(t_key_value *obj,
											t_cylinder *cylinder);

/*
**						sdl_utils
*/

// void					draw_line(t_rect tmp, int color, t_sdl *sdl);
void					change_music(Mix_Music *music[]);
int						render_help_screen(t_sdl *sdl);
void					sdl_loop(t_rt *rt);
void					sdl_quit(t_sdl *sdl);
void					sdl_update(t_sdl *sdl);

/*
**						utils
*/

void					func_error(int err);
void					ft_error(char *str);
int						ft_len_arr(void **arr);
char					*get_next_name(char *name);
cl_int3					int_to_rgb(int src_color);
int						read_kernel(t_cl *cl, char **files_cl);
int						realloc_img(t_scene *scene, char *file_name);
int						filter(int	*pixels, char flag);
int						realloc_obj(SDL_Event event, t_rt *rt);
void					save_image(t_sdl *sdl);
void					show_error(char *error, char *sounds[]);

# endif
#endif
