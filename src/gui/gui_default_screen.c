/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_default_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:44:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/09 06:00:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Texture	*texture;


void	resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
					SDL_Surface *dest_surf, SDL_Surface *src_surf)
{
	// if (env->sdl->resize_flag == 0)
		// SDL_BlitScaled(texture, &srcrect, src_surf, &dstrect);
	// else if (env->sdl->resize_flag == 1)
	SDL_BlitScaled(dest_surf, NULL, src_surf, &dstrect);
	// else if (env->sdl->resize_flag == 2)
		// SDL_BlitScaled(dest_surf, &srcrect, src_surf, NULL);
}

void				render_surface(SDL_Rect srcrect, SDL_Rect dstrect,
								SDL_Surface *dest_surf, SDL_Surface *src_surf)
{
	SDL_Surface		*copy_texture;

	copy_texture = SDL_DuplicateSurface(dest_surf);
	resize_surface(srcrect, dstrect, copy_texture, src_surf);
	SDL_BlitSurface(src_surf, NULL, copy_texture, NULL);
	SDL_FreeSurface(copy_texture);
}

static void	 load_from_rendered_text(SDL_Renderer *render, TTF_Font *font,
									const char *str, SDL_Color color)
{
	SDL_Surface	*txt_surface;
	// SDL_Texture	*texture;

	txt_surface = TTF_RenderText_Solid(font, str, color);
	texture = SDL_CreateTextureFromSurface(render, txt_surface);
	SDL_FreeSurface(txt_surface);
}
void		gui_mode(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 135, 0, 0}, "Mode", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 155, 0, 0}, "Negative", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){350, 155, 0, 0}, "Sepia", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){200, 185, 0, 0}, "Blur", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){350, 185, 0, 0}, "None", gui->ttf[0], sur);
}

void		gui_skybox(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 35, 0, 0}, "Skybox", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 15, 0, 0}, "id", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){265, 15, 0, 0}, "ambient", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){380, 15, 0, 0}, "fsaa", gui->ttf[0], sur);
}

void		gui_default_screen(t_object **hi_lited_object, t_sdl *sdl)
{
	gui_skybox(sdl->gui, sdl->screen[1]->sur);
	gui_mode(sdl->gui, sdl->screen[1]->sur);
	// if (*hi_lited_object)
		// ;
	// render_borders((SDL_Color){255, 0, 0, 0}, (SDL_Rect){0, 3, 50, 20}, sdl);

	// for (size_t i = 0; i < 4; i++)
	// {
		
	// 	if (sdl->gui->radio_btn[i])
	// 	{
	// 		render_surface((SDL_Rect){0, 0, 0, 0}, (SDL_Rect){50, 50 * (i + 1), 70, 36}, sdl->gui->radio_click, sur);
	// 	}
	// 	else
	// 		render_surface((SDL_Rect){0, 0, 0, 0}, (SDL_Rect){50, 50 * (i + 1), 70, 36}, sdl->gui->radio, sur);
	// }
	// // fill_rect((SDL_Rect){3, 3, 44, 14},
	// 		// rgb_to_int(255, 255, 0), sur);
	// sdl->gui->buttons[0]->text = "EXIT";
	// sdl->gui->buttons[0]->clr_button = (SDL_Color){255, 255, 0, 0};
	// sdl->gui->buttons[0]->clr_border = (SDL_Color){255, 0, 0, 0};
	// sdl->gui->buttons[0]->rect_borders = (SDL_Rect){2, 5, 400, 100};
	// sdl->gui->buttons[0]->rect_body = (SDL_Rect){400, 200, 50, 20};
	// render_button(sdl->gui->buttons[0], sdl);

	// load_from_rendered_text(render, sdl->font, "SOSU", (SDL_Color){255, 255, 0, 0});
	// load_from_rendered_text(render, sdl->font, (const char *)sdl->gui->input_text, (SDL_Color){255, 255, 0, 0});
	// SDL_StartTextInput();
	// sdl_putstr((SDL_Rect){100, 10 0, 0}0, "PIDOR", gui->ttf[0], sur);
}
