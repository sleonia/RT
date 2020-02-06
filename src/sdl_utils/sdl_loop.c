/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:30:45 by sleonia           #+#    #+#             */
/*   Updated: 2020/02/07 01:22:27 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define NKC_IMPLEMENTATION


	char			flag;
	SDL_Event		event;
	Uint32			timeout;
	t_object		*hi_lited_object;
	t_rt *rt;

void mainLoop(void* loopArg){
    struct my_nkc_app* myapp = (struct my_nkc_app*)loopArg;
    struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);

    union nkc_event e = nkc_poll_events(myapp->nkcHandle);
    if( (e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) ){
        nkc_stop_main_loop(myapp->nkcHandle);
    }

    /* Nuklear GUI code */
    if (nk_begin(ctx, "Show", nk_rect(50, 50, 220, 220),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            /* event handling */
            printf("Button pressed\n");
        }

        /* fixed widget window ratio width */
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", myapp->op == EASY)) myapp->op = EASY;
        if (nk_option_label(ctx, "hard", myapp->op == HARD)) myapp->op = HARD;

        /* custom widget pixel width */
        nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(ctx, 50);
            nk_label(ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 110);
            nk_slider_float(ctx, 0, &(myapp->value), 1.0f, 0.1f);
        }
        nk_layout_row_end(ctx);
    }
    nk_end(ctx);
    /* End Nuklear GUI */
    nkc_render(myapp->nkcHandle, nk_rgb(40,40,40) );
	events_processing(&flag, &hi_lited_object, rt);
}
void		sdl_loop(t_rt *rt1)
{
	rt = rt1;
struct my_nkc_app myapp;
	struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
    myapp.nkcHandle = &nkcx;
    /* init some user data */
    myapp.value = 0.4;
    myapp.op = HARD;

	if(!nkc_init( myapp.nkcHandle, "Nuklear+ Example", 640, HEIGHT, NKC_WIN_FIXED))
		ft_error("nkc_init");
	hi_lited_object = NULL;
	flag = 0;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	// SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_update(rt->sdl);
	nkc_set_main_loop(myapp.nkcHandle, mainLoop, (void*)&myapp );
	// sdl_quit(rt->sdl);
}