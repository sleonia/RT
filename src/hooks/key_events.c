/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:42:59 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 02:27:33 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		arrows_processing(SDL_Scancode scancode, t_object *hi_lited_object)
{
	if (!hi_lited_object)
		return ;
	if (scancode == SDL_SCANCODE_DOWN)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] -= 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[1] -= 0.17;
	}
	if (scancode == SDL_SCANCODE_UP)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[1] += 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[1] += 0.17;
	}
	if (scancode == SDL_SCANCODE_LEFT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] -= 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[0] -= 0.17;
	}
	if (scancode == SDL_SCANCODE_RIGHT)
	{
		if (hi_lited_object->type == o_sphere)
			hi_lited_object->object.sphere.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_cylinder)
			hi_lited_object->object.cylinder.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_cone)
			hi_lited_object->object.cone.center.v4[0] += 0.17;
		if (hi_lited_object->type == o_parab)
			hi_lited_object->object.parab.center.v4[0] += 0.17;
	}
}

static void		add_obj(SDL_Scancode scancode, t_scene *scene, t_cl *cl)
{
	cl_int		ret;

	ret = 0;
	realloc_obj(scancode, scene);
	clReleaseMemObject(cl->memobjs[2]);
	if ((cl->memobjs[2] = clCreateBuffer(cl->context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_object) * scene->count_objects, scene->object, &ret))
		&& ret != 0)
		ft_error("clCreateBuffer");
}

bool			key_rt(SDL_Scancode scancode, char *flag, t_object *hi_lited_object, t_rt *rt)
{
	move(rt->sdl->event, &(rt->scene->cam), &(rt->scene->flag));
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{
		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (scancode == SDL_SCANCODE_N)
			*flag = NEGATIVE;
		if (scancode == SDL_SCANCODE_M)
			*flag = SEPIA;
		if (scancode == SDL_SCANCODE_K)
			*flag = BLUR;
		if (scancode == SDL_SCANCODE_B)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		if (scancode == SDL_SCANCODE_H)
			SDL_SetWindowTitle(rt->sdl->screen[0]->win, "Peer gay!");
		if (scancode == SDL_SCANCODE_H)
			SDL_ShowSimpleMessageBox(0, "KEK", "KekWait", rt->sdl->screen[0]->win);
		if (scancode == SDL_SCANCODE_J)
			*flag = 0;
		if (scancode == SDL_SCANCODE_KP_0 || scancode == SDL_SCANCODE_KP_1
			|| scancode == SDL_SCANCODE_KP_2 || scancode == SDL_SCANCODE_KP_3
			|| scancode == SDL_SCANCODE_KP_4)
			add_obj(scancode, rt->scene, rt->cl);
		rotation(scancode, rt->sdl, &(rt->scene->cam));
		arrows_processing(scancode, hi_lited_object);
		if (scancode == SDL_SCANCODE_SPACE)
			save_image(rt->sdl);
		rt->scene->move_on = 1;
	}
	return (false);
}

void			str_pop_back(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (!str[i + 1])
		{
			str[i] = '\0';
			break ;
		}
	}
}

bool			key_toolbar(SDL_Scancode scancode, char *flag, t_object *hi_lited_object, t_rt *rt)
{
	if (hi_lited_object)
		return false;
	if (rt->sdl->event.type == SDL_KEYDOWN)
	{

		if (scancode == SDL_SCANCODE_1)
			rt->sdl->gui->radio_btn[0] = !rt->sdl->gui->radio_btn[0];
		if (scancode == SDL_SCANCODE_2)
			rt->sdl->gui->radio_btn[1] = !rt->sdl->gui->radio_btn[1];
		if (scancode == SDL_SCANCODE_3)
			rt->sdl->gui->radio_btn[2] = !rt->sdl->gui->radio_btn[2];
		if (scancode == SDL_SCANCODE_4)
			rt->sdl->gui->radio_btn[3] = !rt->sdl->gui->radio_btn[3];

		if (scancode == SDL_SCANCODE_ESCAPE)
			*flag = 1;
		if (rt->sdl->event.key.keysym.sym == SDLK_BACKSPACE && ft_strlen(rt->sdl->gui->input_text) > 0)
		{
			str_pop_back(rt->sdl->gui->input_text);
			rt->sdl->gui->render_text = true;
		}
		else if(rt->sdl->event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
		{
			SDL_SetClipboardText(rt->sdl->gui->input_text);
		}
		else if(rt->sdl->event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
		{
			rt->sdl->gui->input_text = SDL_GetClipboardText();
			rt->sdl->gui->render_text = true;
		}
	}
	else if(rt->sdl->event.type == SDL_TEXTINPUT)
	{
		if( !( SDL_GetModState() & KMOD_CTRL && (rt->sdl->event.text.text[ 0 ] == 'c' || rt->sdl->event.text.text[ 0 ] == 'C' || rt->sdl->event.text.text[ 0 ] == 'v' || rt->sdl->event.text.text[ 0 ] == 'V' ) ) )
		{
			//Append character
			// rt->sdl->gui->input_text += rt->sdl->event.text.text;
			// rt->sdl->gui->input_text += rt->sdl->event.text.text;
			rt->sdl->gui->new_input_text = ft_strjoin(rt->sdl->gui->input_text, rt->sdl->event.text.text);
			rt->sdl->gui->render_text = true;
		}
	}
	return (false);
}

bool			key_events(char *flag, t_object *hi_lited_object, t_rt *rt)
{
	int			index;
	bool		ismove;

	index = -1;
	ismove = false;
	if (rt->sdl->screen[0]->keyboard_focus)
		ismove |= key_rt(rt->sdl->event.key.keysym.scancode, flag,
						hi_lited_object, rt);
	else if (rt->sdl->screen[1]->keyboard_focus)
		ismove |= key_toolbar(rt->sdl->event.key.keysym.scancode, flag,
							hi_lited_object, rt);
		// if (rt->sdl->event.key.keysym.scancode == SDL_SCANCODE_1) //фокус работает, но хуево работает
		// {
			// if ((!rt->sdl->screen[1]->keyboard_focus || !rt->sdl->screen[1]->mouse_focus))
			// 	index = 1;
			// else if ((!rt->sdl->screen[0]->keyboard_focus || !rt->sdl->screen[0]->mouse_focus))
			// 	index = 0;
			// if (index != -1)
			// {
			// 	SDL_ShowWindow(rt->sdl->screen[index]->win);
			// 	SDL_RaiseWindow(rt->sdl->screen[index]->win);
			// 	rt->sdl->screen[index]->shown = true;
			// 	rt->sdl->screen[index]->keyboard_focus = true;
			// 	rt->sdl->screen[index]->mouse_focus = true;
			// }
		// }
	return (ismove);
}
