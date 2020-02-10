/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_default_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 06:44:01 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 04:40:14 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Texture	*texture;


void	resize_surface(SDL_Rect srcrect, SDL_Rect dstrect,
					SDL_Surface *dest_surf, SDL_Surface *src_surf)
{
	srcrect.x = 0; //gcc -www
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

void		gui_mode(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 315, 0, 0}, "Mode", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 345, 0, 0}, "Negative", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){350, 345, 0, 0}, "Sepia", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){200, 375, 0, 0}, "Blur", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){350, 375, 0, 0}, "None", gui->ttf[0], sur);
}

void		gui_skybox(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 175, 0, 0}, "Skybox", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 155, 0, 0}, "id", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){265, 155, 0, 0}, "ambient", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){400, 155, 0, 0}, "fsaa", gui->ttf[0], sur);
}

void		gui_camera(t_gui *gui, SDL_Surface *sur)
{
	sdl_putstr((SDL_Rect){15, 35, 0, 0}, "Camera", gui->ttf[1], sur);
	sdl_putstr((SDL_Rect){200, 15, 0, 0}, "phi", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){265, 15, 0, 0}, "position", gui->ttf[0], sur);
	sdl_putstr((SDL_Rect){400, 15, 0, 0}, "tetta", gui->ttf[0], sur);
}

void		gui_default_screen(t_object **hi_lited_object, t_sdl *sdl)
{
	if (*hi_lited_object)
		;
	sdl->gui->ttf[0]->font_color = (SDL_Color){209, 191, 155, 0};
	gui_camera(sdl->gui, sdl->screen[1]->sur);
	gui_skybox(sdl->gui, sdl->screen[1]->sur);
	gui_mode(sdl->gui, sdl->screen[1]->sur);
	// render_borders((SDL_Color){255, 0}, (SDL_Rect){0, 3, 50, 20}, sdl);

	// for (size_t i = 0; i < 4; i++)
	// {
		
	// 	if (sdl->gui->radio_btn[i])
	// 	{
	// 		render_surface((SDL_Rect){0, 0}, (SDL_Rect){50, 50 * (i + 1), 70, 36}, sdl->gui->radio_click, sur);
	// 	}
	// 	else
	// 		render_surface((SDL_Rect){0, 0}, (SDL_Rect){50, 50 * (i + 1), 70, 36}, sdl->gui->radio, sur);
	// }
	// // fill_rect((SDL_Rect){3, 3, 44, 14},
	// 		// rgb_to_int(255, 255, 0), sur);
	sdl->gui->buttons[0]->text = "Exit";
	sdl->gui->buttons[0]->clr_button = (SDL_Color){0, 255, 0, 0};
	sdl->gui->buttons[0]->clr_border = (SDL_Color){255, 0, 0, 0};
	sdl->gui->buttons[0]->rect_borders = (SDL_Rect){0, 450, 410, 110};
	sdl->gui->buttons[0]->rect_body = (SDL_Rect){5, 455, 400, 100};
	render_button(sdl->gui->buttons[0], sdl);

	sdl->gui->buttons[1]->text = "New object";
	sdl->gui->buttons[1]->clr_button = (SDL_Color){209, 191, 155, 0};
	sdl->gui->buttons[1]->clr_border = (SDL_Color){255, 0, 0, 0};
	// sdl->gui->buttons[1]->rect_borders = (SDL_Rect){0, 700, 210, 70};
	sdl->gui->buttons[1]->rect_body = (SDL_Rect){5, 705, 200, 60};
	render_button(sdl->gui->buttons[1], sdl);

	sdl->gui->buttons[2]->text = "Screenshot";
	sdl->gui->buttons[2]->clr_button = (SDL_Color){209, 191, 155, 0};
	sdl->gui->buttons[2]->clr_border = (SDL_Color){255, 0, 0, 0};
	// sdl->gui->buttons[2]->rect_borders = (SDL_Rect){300, 700, 210, 70};
	sdl->gui->buttons[2]->rect_body = (SDL_Rect){305, 705, 200, 60};
	render_button(sdl->gui->buttons[2], sdl);

	// load_from_rendered_text(render, sdl->font, "SOSU", (SDL_Color){255, 255});
	// load_from_rendered_text(render, sdl->font, (const char *)sdl->gui->input_text, (SDL_Color){255, 255});
	// SDL_StartTextInput();
	// sdl_putstr((SDL_Rect){100, 10 0, 0}0, "PIDOR", gui->ttf[0], sur);
}
