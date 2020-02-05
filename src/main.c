/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:57:07 by deladia           #+#    #+#             */
/*   Updated: 2020/02/05 23:45:05 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// int			main(int ac, char **av)
// {
// 	t_rt		*rt;

// 	if (ac != 2)
// 		ft_error(ERROR_INPUT);
// 	rt = init_rt(av);
// 	change_music(rt->sdl->music);
// 	calc_screen(&rt->scene->cam);
// 	set_opencl_arg(rt->opencl, rt->sdl, rt->scene);
// 	sdl_loop(rt);
// 	return (0);
// }

typedef struct			s_windows
{
	SDL_Window			*mWindow;
	SDL_Renderer		*mRenderer;
	int					mWindowID;

	//Window dimensions
	int					mWidth;
	int					mHeight;

	//focus
	bool				mMouseFocus;
	bool				mKeyboardFocus;
	bool				mFullScreen;
	bool				mMinimized;
	bool				mShown;
}						t_windows;


void	init(t_windows *win)
{
	win->mWindow = NULL;
	win->mRenderer = NULL;

	win->mMouseFocus = false;
	win->mKeyboardFocus = false;
	win->mFullScreen = false;
	win->mShown = false;
	win->mWindowID = -1;

	win->mWidth = 0;
	win->mHeight = 0;
	if (!(win->mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE )))
		exit (1);
	win->mMouseFocus = true;
	win->mKeyboardFocus = true;
	win->mWidth = WIDTH;
	win->mHeight = HEIGHT;
	if (!(win->mRenderer = SDL_CreateRenderer( win->mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC )))
		exit (1);
	SDL_SetRenderDrawColor(win->mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	win->mWindowID = SDL_GetWindowID(win->mWindow);
	win->mShown = true;
}

void	render(t_windows *win)
{
	if (win->mMinimized)
	{
		SDL_SetRenderDrawColor(win->mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(win->mRenderer);
		SDL_RenderPresent(win->mRenderer);
	}
}

int main( int argc, char* args[])
{

	t_windows **win;
	win = (t_windows **)malloc(sizeof(t_windows *) * 3);

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		exit (1);
	}
	//Set texture filtering to linear
	if( ! SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
		
	}
	for (size_t i = 0; i < 3; i++)
	{
		win[i] = (t_windows *)malloc(sizeof(t_windows));
		init(win[i]);
	}
	bool quit = false;
	SDL_Event e;
	while( !quit )
	{
		// while( SDL_PollEvent( &e ) != 0 )
		// {
		// 	//
		// }
		for (size_t i = 0; i < 3; i++)
		{
			render(win[i]);
		}
		bool allWindowsClosed = true;
		for (size_t i = 0; i < 3; i++)
		{
			if (win[i]->mShown)
			{
				allWindowsClosed = false;
				break ;
			}
		}
		if( allWindowsClosed )
		{
			quit = true;
		}
	}
	exit(1);
}