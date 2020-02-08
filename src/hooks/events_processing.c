/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_processing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:38:10 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/08 07:48:26 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern SDL_Texture	*texture;

void		 load_from_rendered_text(SDL_Renderer *render, TTF_Font *font,
									const char *str, SDL_Color color)
{
	SDL_Surface	*txt_surface;
	// SDL_Texture	*texture;

	txt_surface = TTF_RenderText_Solid(font, str, color);
	texture = SDL_CreateTextureFromSurface(render, txt_surface);
	SDL_FreeSurface(txt_surface);
}

void			events_processing(char *flag, t_object **hi_lited_object, t_rt *rt)
{
	bool		ismove;

	ismove = false;
	while (SDL_PollEvent(&rt->sdl->event))
	{
		if (rt->sdl->event.type == SDL_QUIT) //не работает
			*flag = 1;
		window_events(rt->sdl->event, rt->sdl->screen[0]);
		window_events(rt->sdl->event, rt->sdl->screen[1]);
		ismove |= key_events(flag, *hi_lited_object, rt);
		ismove |= mouse_events(flag, rt->sdl, hi_lited_object, rt->scene);
	}

if(rt->sdl->gui->render_text)
{
	//Text is not empty
	if(ft_strcmp(rt->sdl->gui->new_input_text, "") == 1)
	// if(rt->sdl->gui->new_input_text != "")
	{
		//Render new text
	load_from_rendered_text(rt->sdl->screen[1]->render, rt->sdl->font, rt->sdl->gui->input_text, (SDL_Color){255, 255, 0, 0});
	}
	//Text is empty
	else
	{
		load_from_rendered_text(rt->sdl->screen[1]->render, rt->sdl->font, " ", (SDL_Color){255, 255, 0, 0});
	}
}

	
	if (ismove == false)
		rt->scene->move_on = 0;
	calc_screen(&rt->scene->cam);
	create_kernel_rt(rt->cl, rt->scene);
	set_opencl_arg(rt->cl, rt->sdl, rt->scene);
	filter(rt->sdl->screen[0]->sur->pixels, *flag);
	if (*flag == BLUR && !rt->scene->move_on)
		create_kernel_blur(rt->cl, rt->sdl);
	sdl_update(hi_lited_object, rt->sdl);
}
