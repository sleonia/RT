#include <SDL.h>
#include <vector>

struct window_data
{
    SDL_Rect bounds;
    SDL_Window *window;
    SDL_Renderer* renderer;
};

int main( int argc, char **argv )
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return EXIT_FAILURE;

    std::vector< window_data > screens( SDL_GetNumVideoDisplays() );
    for( size_t i = 0; i < screens.size(); ++i )
    {
        window_data& screen = screens[ i ];
        SDL_GetDisplayBounds( i, &screen.bounds );
        screen.window = SDL_CreateWindow
            ( 
            "Display", 
            screen.bounds.x, screen.bounds.y, 
            screen.bounds.w, screen.bounds.h, 
            SDL_WINDOW_BORDERLESS
            );
        screen.renderer = SDL_CreateRenderer( screen.window, 0, SDL_RENDERER_ACCELERATED );
        SDL_ShowWindow( screen.window );
    }

    bool running = true;
    while( running )
    {
        SDL_Event ev;
        while( SDL_PollEvent( &ev ) )
        {
            if( ev.type == SDL_QUIT )  running = false;
            if( ev.type == SDL_KEYUP &&
                ev.key.keysym.sym == SDLK_ESCAPE ) running = false;
        }

        for( size_t i = 0; i < screens.size(); ++i )
        {
            window_data& screen = screens[ i ];
            SDL_SetRenderDrawColor( screen.renderer, 255, 0, 0, 255 );
            SDL_RenderFillRect( screen.renderer, NULL );
            SDL_RenderPresent( screen.renderer );
        }

        SDL_Delay( 33 );
    }

    for( size_t i = 0; i < screens.size(); ++i )
    {
        window_data& screen = screens[ i ];
        SDL_DestroyRenderer( screen.renderer );
        SDL_DestroyWindow( screen.window );
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}