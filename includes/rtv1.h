/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deladia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:18:10 by deladia           #+#    #+#             */
/*   Updated: 2019/11/04 02:47:37 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

# include "libft.h"
# include <SDL.h>
# include <math.h>
# define WIDTH 1000
# define HEIGHT 1000
# define VW 1.0472
# define VH 1.0472
# define D 1
# define BLACK 0x000000

typedef struct			s_result
{
	double				t1;
	double				t2;
}						t_result;

typedef struct			s_pos
{
	double				x;
	double				y;
	double				z;
}						t_pos;

typedef struct			s_light
{
	char				type;
	double				intensity;
	t_pos				position;
	struct s_light		*next;
}						t_light;

typedef struct			s_light_params
{
	char				type;
	double				intensity;
	t_pos				pos;
}						t_light_params;

typedef struct			s_cylinder
{
	t_pos				center;
	t_pos				axis;
	double				radius;
}						t_cylinder;

typedef struct			s_plane
{
	t_pos				center;
	t_pos				normal;
}						t_plane;

typedef struct			s_cone
{
	t_pos				center;
	t_pos				axis;
	double				radius;
}						t_cone;

typedef struct			s_sphere
{
	t_pos				center;
	double				radius;
}						t_sphere;

union					u_objects
{
	t_sphere			sphere;
	t_cylinder			cylinder;
	t_cone				cone;
	t_plane				plane;
};

enum					e_obj_type
{
	o_sphere = 1,
	o_cylinder,
	o_cone,
	o_plane,
};


typedef struct			s_object
{
	union u_objects		*objects;
	enum e_obj_type		type;
	int					color;
	int					specular;
	double				reflective;
	struct s_object		*next;
}						t_object;

typedef struct			s_discriminant
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
}						t_discriminant;

typedef struct			s_min_max
{
	double				min;
	double				max;
}						t_min_max;

typedef struct			s_cylinder_params
{
	t_pos				pos;
	t_pos				axis;
	double				radius;
	int					color;
	int					specular;
	double				reflective;
}						t_cylinder_params;

typedef struct			s_cone_params
{
	t_pos				pos;
	double				radius;
	int					color;
	int					specular;
	double				reflective;
	t_pos				axis;
}						t_cone_params;

typedef struct			s_plane_params
{
	t_pos				pos;
	int					color;
	int					specular;
	double				reflective;
	t_pos				normal;
}						t_plane_params;

typedef struct			s_sphere_params
{
	t_pos				pos;
	double				radius;
	int					color;
	int					specular;
	double				reflective;
}						t_sphere_params;

typedef struct			s_return
{
	t_object			*closest_obj;
	double				closest_t;
}						t_return;

typedef struct s_for_ray_trace
{
	int local_color;
	int reflected_color;
	t_return ret;
}				t_for_ray_trace;

typedef struct			s_cam
{
	t_pos				position;
	double				a;
	double				b;
}						t_cam;

typedef struct			s_light_off
{
	short int			ambient;
	short int			point;
	short int			directional;
	short int			reflect;
}						t_light_off;

typedef struct			s_scene
{
	t_pos				*view;
	t_cam				*cam;
	t_light				*light;
	t_object			*object;
	t_light_off			*off;
	int					depth;
}						t_scene;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Renderer		*render;
	SDL_Texture			*texture;
	SDL_Event			event;
	int					*pixels;
}						t_sdl;

typedef struct			s_rtv1
{
	t_sdl				*sdl;
	t_scene				*scene;
}						t_rtv1;

t_pos					insert(int x, int y, int z);
t_pos					*canvas_to_viewport(int x, int y, t_pos *pos);
t_pos					vector_minus(t_pos *o, t_pos	*center);
double					dot(t_pos *a, t_pos *b);
int						sdl_init(t_sdl *sdl);
int						sdl_control(t_sdl *sdl, t_scene *scene);
int						*put_pixel(double x, double y, int color, t_sdl *sdl);
t_pos					vector_pus(t_pos *o, t_pos *center);
t_pos					vector_on_number(t_pos *o, double nbr);
t_pos					vector_div(t_pos *o, double nbr);
double					vector_len(t_pos *o);
t_pos					vector_normalize(t_pos *a);
double					computer_lighting(t_pos *p, t_pos *n, t_pos *v, int s,
							t_scene *scene);
void					ft_error(char *str);
t_return				closest_intersection(t_pos *o, t_pos *d, t_min_max mn, t_object *obj);
int						trace_start(t_sdl *sdl, t_scene *scene);
t_pos					*vector_on_vector(t_pos *a, t_pos *b, t_pos *ab);
t_pos					*matrix_on_vector(double a, double b, t_pos *vec);
int						trace_ray(t_pos *o, t_pos *d, t_min_max mn, t_scene *scene);
t_object				*init_sphere(t_object *obj, t_sphere_params params);
t_object				*init_cylinder(t_object *obj, t_cylinder_params params);
void					init_scene(t_scene *scene);
void					sdl_error(char *str);
void					sdl_control_1(t_sdl *sdl, t_scene *scene);
void					sdl_control_2(t_sdl *sdl, t_scene *scene);
void					sdl_control_3(t_sdl *sdl, t_scene *scene);
void					sdl_control_4(t_sdl *sdl, t_scene *scene);
void					sdl_control_5(t_sdl *sdl, t_scene *scene);
void					sdl_control_6(t_sdl *sdl, t_scene *scene);
t_result				get_intersect(t_pos *o, t_pos *d, t_object *obj);
t_pos					get_obj_normal(t_pos *p, t_return *ret, t_pos *o, t_pos *d);
t_pos					v_minus(t_pos v1, t_pos v2);
t_pos					v_plus(t_pos v1, t_pos v2);

#endif
