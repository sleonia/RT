#include "rtv1.h"
#include <math.h>

int 	sdl_init(void)
{	SDL_Window		*window = NULL;
	SDL_Renderer	*ren = NULL;
	SDL_Texture		*tex;
	char 			quit = 0;
	SDL_Event		e;
	SDL_Keysym		key;
	int				*pixels;
	SDL_PixelFormat	*ftm;

	//Инициальзация нужных подсистем
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		printf("SDL_Init Error: %s", SDL_GetError());
		return (1);
	}
	//Создание окна (название, х, у, ширина, высота, флаги)
	if ((window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	{
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		return (1);
	}
	//Создание рендера для рисования (окно, индекс драйвера(-1, тогда сам найдет нужный), флаги на тип рендера)
	if ((ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return (1);
	}

//	//Загрузка в память картинки
//	if ((sur = SDL_CreateRGBSurfaceFrom((void *)arr, SCREEN_WIDTH, SCREEN_HEIGHT, 24, SCREEN_WIDTH * 3, 0x0000FF, 0x00FF00, 0xFF0000, 0)) == NULL)
//	{
//		printf("SDL_LoadBMP Error: %s", SDL_GetError());
//		return (1);
//	}
//////	//Загрузка картинки в рендер
	if ((tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT)) == NULL)
	{
		printf("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		return (1);
	}
	pixels = (int *)ft_memalloc(sizeof(int) * SCREEN_WIDTH * SCREEN_HEIGHT);
//    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_UpdateTexture(tex, NULL, pixels, SCREEN_WIDTH * sizeof(int));
//	SDL_UpdateTexture(tex, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
//	SDL_LockTexture(tex, &bmp->pixels, &pixels, bmp->pitch);
//	memcpy(pixels, bmp->pixels, bmp->w * bmp->h);
	//Больше не потребуется чистим
//	SDL_FreeSurface(bmp);


	//SetRenderDrawColor в сочетании с RenderClear заполняет экран выбранным цветом
//	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
//	SDL_RenderClear(ren);

	//Ставлю цвет рендеринга
//	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	//Ставлю пиксель заданого цвета
//	SDL_RenderDrawPoint(ren, 320, 240);
	//Вывожу на экран
//	SDL_RenderPresent(ren);
	int i = 320;
	int j = 240;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			//ивент нажата кнопка
			if (e.type == SDL_KEYDOWN)
			{
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				SDL_RenderClear(ren);
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				//сравниваем с тем что нажато и делаем то что нужно
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					i -= 2;
				if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					i += 2;
				if (e.key.keysym.scancode == SDL_SCANCODE_UP)
					j -= 2;
				if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					j += 2;
				int g = 0;
				while(g < SCREEN_HEIGHT * SCREEN_WIDTH)
				{
					pixels[g] = 0x0000FF + 1 + g;
					g++;
				}
//				pixels[200 * 100] = 0xFF0000;
//				pixels[201 * 100] = 0xFF0000;
//				pixels[202 * 100] = 0xFF0000;
				SDL_UpdateTexture(tex, NULL, pixels, SCREEN_WIDTH * sizeof(int));
				SDL_RenderCopy(ren, tex, NULL, NULL);
				SDL_RenderDrawPoint(ren, i, j);
				SDL_RenderPresent(ren);
//				SDL_RenderDrawRect(ren, NULL);
			}

		}

		//Очищаем рендер, отрендерим текстуру и выведем на экран
//		SDL_RenderClear(ren);
//		SDL_RenderCopy(ren, tex, NULL, NULL);

	}
	//Уборка мусора
//	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}

int		main()
{
	int 	sx;
	int 	sy; //координаты в представлении экрана
	int 	cx;
	int 	cy; //координаты в нашем представлении

	//холст
	int 	vw = 200;
	int 	vh = 200;
	int 	d = 200;
	int 	vx;
	int 	vy;
	int 	vz;

	//перевод в координаты экрана из нашей системы координат
	sx = SCREEN_WIDTH / 2 + cx;
	sy = SCREEN_HEIGHT / 2 - cy;

	//определяем квадрат сетки соответсвующий этому пикселю
	// для каждого пикселя (Сх, Су) холста определяем соответсвующую точку окна просмотра (Vx, Vy, Vz)
	vx = cx * vw / SCREEN_WIDTH;
	vy = cy * vh / SCREEN_HEIGHT;
	vz = d;


	sdl_init();
	return (0);
}