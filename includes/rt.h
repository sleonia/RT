/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 04:06:50 by thorker           #+#    #+#             */
/*   Updated: 2020/02/21 04:54:42 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RT_H
# define RT_RT_H

# ifndef OPENCL___
#  include "libft.h"
#  include "to_json.h"
#  include "rt_error.h"
#  include "gui.h"
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
#  define AXIS_FLAG 0
#  define CENTER_FLAG 1
#  define COLOR_FLAG 2
#  define STEP 0.1
#  define NEGATIVE -101
#  define SEPIA -102
#  define BLUR -103
#  define NBR_OF_SONGS		20
#  define CNT_OF_DISPLAYS	2
#  define DISPLAY_NOT	"osascript -e \'display notification\""
#  define FONT			"./assets/fonts/open-sans/OpenSans-Regular.ttf"
# endif
# define WIDTH 1280
# define HEIGHT 1024
# define TOOL_SCREEN_WIDTH 500
# define TOOL_SCREEN_HEIGHT HEIGHT
# define MAX_DIST 10000.f

typedef struct			s_move_flag
{
	char				w;
	char				s;
	char				d;
	char				a;
	char				v;
	char				c;
}						t_move_flag;

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

typedef struct			s_parab
{
# ifndef OPENCL___

	cl_float3			center;
	cl_float3			axis;
# else

	float3				center;
	float3				axis;
# endif

	float				k;
	float				length;
}						t_parab;

typedef struct			s_torus
{
# ifndef OPENCL___

	cl_float3			center;
	cl_float3			axis;
# else

	float3				center;
	float3				axis;
# endif

	float				bigr;
	float				r;
}						t_torus;

union					u_objects
{
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
	t_plane				plane;
	t_parab				parab;
	t_torus				torus;
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
	o_parab,
	o_torus
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
	t_move_flag			flag;
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
	cl_mem				memobjs[7];
	char				**program_source;
	size_t				*program_size;
	size_t				count_files;
	char				**files;
}						t_cl;

typedef struct			s_screen
{
	SDL_Window			*win;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	SDL_Surface			*sur;
	int					win_id;
	bool				mouse_focus;
	bool				keyboard_focus;
	bool				full_screen;
	bool				minimized;
	bool				shown;
}						t_screen;

typedef struct			s_sdl
{
	t_gui				*gui;
	t_screen			*screen[2];
	Mix_Music			*music[NBR_OF_SONGS];
	char				*sounds[NBR_OF_SONGS];
	SDL_Event			event;
	int					volume;
}						t_sdl;

typedef struct			s_rt
{
	t_sdl				*sdl;
	t_cl				*cl;
	t_scene				*scene;
}						t_rt;
# endif

# ifndef OPENCL___

/*
**						gui
*/
void					gui_buttons(t_sdl *sdl);
void					set_value_in_def_textbox(t_scene *scene,
											t_gui *gui);
void					set_textbox_value(t_scene *scene,
										t_object **hi_lited_object,
										t_gui *gui);
void					gui_default_screen(char *flag,
										t_sdl *sdl);
void					gui_cone_screen(t_sdl *sdl);
void					gui_cylinder_screen(t_sdl *sdl);
void					gui_parab_screen(t_sdl *sdl);
void					gui_plane_screen(t_sdl *sdl);
void					gui_sphere_screen(t_sdl *sdl);
void					gui_torus_screen(t_sdl *sdl);

void					gui_main(char *flag,
								t_object **hi_lited_object,
								t_sdl *sdl,
								t_scene *scene);
void					gui_material(t_sdl *sdl);
/*
**						hooks
*/

void					arrows_processing(SDL_Scancode scancode,
										t_object *hi_lited_object);
bool					check_textbox(int x, int y,
									t_object **hi_lited_object,
									t_textbox *textbox[]);
void					events_processing(char *quit,
										t_object **hi_lited_object,
										t_rt *rt);
t_object				*get_object(t_scene *scene, int x, int y);
char					*pop_back(char *str);
int						get_width(t_textbox *textbox);
int						get_height(t_textbox *textbox);
void					add_obj(SDL_Scancode scancode,
						t_scene *scene, t_cl *cl);
void					change_focus(t_sdl *sdl);
bool					key_events(char *quit, t_object **hi_lited_object,
						t_rt *rt);
bool					key_rt(SDL_Scancode scancode,
								char *flag,
								t_object **hi_lited_object,
								t_rt *rt);
bool					key_toolbar(SDL_Scancode scancode,
									char *flag,
									t_object **hi_lited_object,
									t_rt *rt);
bool					mouse_events(char *flag,
									t_object **hi_lited_object,
									t_rt *rt);
void					mouse_rotation(t_cam *cam, int x, int y);
void					move(SDL_Event event, t_cam *cam, t_move_flag *flag);
bool					mouse_rt(t_sdl *sdl,
								t_object **hi_lited_object,
								t_scene *scene);
bool					mouse_toolbar(char *flag,
									t_object **hi_lited_object,
									t_rt *rt);
void					rotation(SDL_Scancode scancode, t_cam *cam);
bool					window_events(char *flag,
									SDL_Event event,
									t_screen *screen);

/*
**						init
*/

char					**init_cl_files(void);
void					create_kernel_blur(t_cl *cl, t_sdl *sdl);
void					create_kernel_rt(t_cl *cl);
void					create_cl(t_cl *cl, t_scene *scene);
void					init_light(t_light **light, int nbr);
void					init_objects(t_object **object, int nbr);
int						set_opencl_arg(t_cl *cl, t_sdl *sdl, t_scene *scene);
int						set_opencl_arg_for_blur(t_cl *cl, t_sdl *sdl);
t_cl					*init_cl(t_rt *rt);
t_gui					*init_gui(void);
t_rt					*init_rt(char **av);
t_scene					*init_scene(t_key_value *json, char *sounds[]);
t_sdl					*init_sdl(t_key_value *json);
int						*fill_texture_for_object(char *texture_path,
											int *texture_pixels,
											int *texture_param);
void					init_textbox(t_gui *gui);

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
float					cl_length_v2(cl_float2 v);

/*
**						parse
*/

void					parse_sounds_json(t_key_value *assets, t_sdl *sdl);
void					parse_music_json(t_key_value *assets, t_sdl *sdl);
void					parse_array_of_float(t_array *array, cl_float3 *pos);
int						parse_volume_json(t_key_value *assets);
void					parse_texture(t_key_value *json, t_scene *scene);
char					*parse_icon_json(t_key_value *assets);
t_key_value				*parse_assets(t_key_value *json);

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
void					parse_parab_json(t_key_value *obj, t_parab *parab);
void					parse_torus_json(t_key_value *obj, t_torus *tor);
void					parse_cylinder_json(t_key_value *obj,
											t_cylinder *cylinder);

/*
**						sdl_utils
*/

void					fill_rect(SDL_Rect tmp, int color, SDL_Surface *sur);
void					change_music(Mix_Music *music[]);
void					render_button(t_button *button, t_sdl *sdl);
void					render_surface(SDL_Rect srcrect, SDL_Rect dstrect,
									SDL_Surface *surface, t_sdl *sdl);
void					sdl_loop(t_rt *rt);
void					sdl_putstr(SDL_Rect	dest,
								char *text,
								t_ttf *ttf,
								SDL_Surface *sur);
void					sdl_quit(t_sdl *sdl);
void					sdl_update(t_object *hi_lited_object, t_sdl *sdl);

/*
**						utils
*/

double					check_phi(double input_phi);
double					check_tetta(double input_tetta);
int						check_skybox(int input_skybox, int texture_cnt);
double					check_ambient(double input_ambient);
int						check_fsaa(int input_fsaa);
void					check_float_array(int flag, cl_float3 *pos);
double					check_length(double input_length);
double					check_radius(double input_radius);
double					check_tan(double input_tan);
double					check_dist(double input_tan);

void					func_error(int err);
char					*float_array_to_string(cl_float3 array);
void					ft_destroy_string_arr(char **arr);
void					ft_error(char *str);
int						ft_len_arr(void **arr);
char					*ft_strjoin_free(char *s1, char *s2, int num);
char					*get_next_name(char *name);
cl_int3					int_to_rgb(int src_color);
void					load_textboxes(int start,
									int end,
									t_gui *gui,
									SDL_Renderer *render);
void					new_sphere(t_object *obj);
void					new_cylinder(t_object *obj);
void					new_cone(t_object *obj);
void					new_plane(t_object *obj);
void					new_parab(t_object *obj);
void					new_torus(t_object *obj);
int						read_kernel(t_cl *cl, char **files_cl);
int						realloc_img(t_scene *scene, char *file_name);
int						filter(int	*pixels, char flag);
int						realloc_obj(SDL_Scancode scancode, t_scene *scene);
int						rgb_to_int(int red, int green, int blue);
void					render_textboxs(int start,
										int end,
										t_gui *gui,
										SDL_Renderer *render);
void					save_image(int *pixels);
void					show_error(char *error, char *sounds[]);
cl_float3				*string_to_float_array(char *str);
int						type_sphere(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist);
int						type_cylinder(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist);
int						type_plane(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist);
int						type_cone(cl_float3 o, cl_float3 d,
								t_object *object, cl_float2 *dist);
int						type_parab(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist);
int						type_torus(cl_float3 o, cl_float3 d,
									t_object *object, cl_float2 *dist);
int						redred(int	color);
int						greengreen(int	color);
int						blueblue(int	color);
float					minn(float a, float b);
void					change_mode(int x, int y, char *flag);
void					check_buttons(char *flag, int x, int y, t_rt *rt);
bool					reset_value(int flag, t_textbox *t_textbox[]);
cl_float3				*string_to_color(char *str);
char					*color_to_string(cl_float3 array);

# endif
#endif
