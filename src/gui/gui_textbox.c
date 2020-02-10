/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_textbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:04:03 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/10 15:25:24 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// void	load_from_rendered_text(t_textbox *textbox, char *text, SDL_Color color)
// {
// 	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text, color);
// 	if( textSurface != NULL )
// 	{
//         lox->mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
// 		if( lox->mTexture == NULL )
// 		{
// 			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
// 			exit (1);
// 		}
// 		else
// 		{
// 			lox->mWidth = textSurface->w;
// 			lox->mHeight = textSurface->h;
// 		}
// 		SDL_FreeSurface( textSurface );
// 	}
// 	else
// 	{
// 		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
// 		exit (1);
// 	}
// }