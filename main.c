#include "rtv1.h"
#include <math.h>

void		sdl_error(char *str)
{
	ft_putstr(str);
	ft_putstr(SDL_GetError());
	write(1, "\n", 1);
	exit (1);
}

void		ft_error(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
	exit (1);
}

int 		sdl_control(t_sdl *sdl)
{
	char 	quit;
	int 	g;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&sdl->event))
		{
			if (sdl->event.type == SDL_QUIT)
				quit = 1;
			//ивент нажата кнопка
			if (sdl->event.type == SDL_KEYDOWN)
			{
				//сравниваем с тем что нажато и делаем то что нужно
				if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				g = 0;
//				while(g < HEIGHT * WIDTH)
//				{
//					sdl->pixels[g] = 0x0000FF + 1 + g;
//					g++;
//				}
				SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(int));
				SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
				SDL_RenderPresent(sdl->render);
			}

		}
	}
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->render);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	return (0);
}

int 		sdl_init(t_sdl *sdl)
{
	//Инициальзация нужных подсистем
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		sdl_error("SDL_Init Error: ");
	//Создание окна (название, х, у, ширина, высота, флаги)
	if ((sdl->window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
		sdl_error("SDL_CreateWindow Error: ");
	//Создание рендера для рисования (окно, индекс драйвера(-1, тогда сам найдет нужный), флаги на тип рендера)
	if ((sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
		sdl_error("SDL_CreateRenderer Error: ");
	//Cоздание пустой текстуры в формате ARGB8888
	if ((sdl->texture = SDL_CreateTexture(sdl->render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)) == NULL)
		sdl_error("SDL_CreateTextureFromSurface Error: ");
	//Создание массива цветов
	if (!(sdl->pixels = (int *)ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		ft_error("Error pixels memory allocation");
	SDL_UpdateTexture(sdl->texture, NULL, sdl->pixels, WIDTH * sizeof(int));
	SDL_RenderClear(sdl->render);
	SDL_RenderCopy(sdl->render, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->render);

//	sdl_control(sdl);

	//уборка мусора
//	SDL_DestroyTexture(sdl->texture);
//	SDL_DestroyRenderer(sdl->render);
//	SDL_DestroyWindow(sdl->window);
//	SDL_Quit();
	return (0);
}

t_pos		*insert(x, y, z)
{
	t_pos	*pos;

	pos = (t_pos *)ft_memalloc(sizeof(t_pos));
	pos->x = x;
	pos->y = y;
	pos->z = z;
	return (pos);
}

t_pos		*CanvasToViewport(int x, int y, t_pos *pos)
{
	pos->x = (double)x * VW / WIDTH;
	pos->y = (double)y * VH / HEIGHT;
	pos->z = D;
	return (pos);
}

t_pos		VectorMinus(t_pos *o, t_pos	*center)
{
	t_pos	oc;

	oc.x = o->x - center->x;
	oc.y = o->y - center->y;
	oc.z = o->z - center->z;
	return (oc);
}

double 		Dot(t_pos *a, t_pos *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_result	*IntersectRaySphere(t_cam *o, t_view *d, t_sphere *sphere)
{
	t_pos		oc;
	t_result	*res;
	double		k1;
	double		k2;
	double		k3;
	double		discriminant;

	res = (t_result *)ft_memalloc(sizeof(t_result));
	oc = VectorMinus(o->position, sphere->center);

	k1 = Dot(d->position, d->position);
	k2 = 2 * Dot(&oc, d->position);
	k3 = Dot(&oc, &oc) - sphere->radius * sphere->radius;

	discriminant = k2 * k2 - 4 * k1 * k3;
	if (discriminant < 0)
	{
		res->t1 = INFINITY;
		res->t2 = INFINITY;
		return (res);
	}
	res->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	res->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
//	printf ("%f %f\n", res->t1, res->t2);
	return (res);
}

int			TraceRay(t_cam *o, t_view *d, double t_min, double t_max, t_sphere *sphere)
{
	double		closest_t;
	t_sphere	*closest_sphere;
	t_result	*res;
	t_sphere	*tmp;

	closest_t = INFINITY;
	closest_sphere = NULL;
	tmp = sphere;
	while (tmp)
	{
		res = IntersectRaySphere(o, d, tmp);
//		printf ("%f %f\n", res->t1, res->t2);
		if (res->t1 >= t_min && res->t1 <= t_max && res->t1 < closest_t)
		{
			closest_t = res->t1;
			closest_sphere = tmp;
		}
		else if (res->t2 >= t_min && res->t2 <= t_max && res->t2 < closest_t)
		{
			closest_t = res->t2;
			closest_sphere = tmp;
		}
		tmp = tmp->next;
	}
//	printf ("%f %f\n", res->t1, res->t2);
	if (closest_sphere == NULL)
		return (WHITE);
	return (closest_sphere->color);
}

int 		*put_pixel(double x, double y, int color, t_sdl *sdl)
{
	int		xnew;
	int		ynew;

	xnew = WIDTH / 2 + (int)x;
	ynew = HEIGHT / 2 - (int)y;
//	printf("%d \n", (int)xnew + (int)ynew * WIDTH);
	sdl->pixels[xnew + ynew * WIDTH] = color;
	return (sdl->pixels);
}

t_sphere	*init_sphere(t_sphere *sphere)
{
	t_sphere	*tmp;
	t_pos		*center;

	sphere = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	sphere->radius  = 1;
	sphere->color = 0xFF0000;
	sphere->center = insert(0, -1, 3);

	sphere->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	tmp = sphere->next;
	tmp->radius  = 1;
	tmp->color = 0x0000FF;
	tmp->center = insert(2, 0, 4);

	tmp->next = (t_sphere *)ft_memalloc(sizeof(t_sphere));
	tmp = tmp->next;
	tmp->radius  = 1;
	tmp->color = 0x00FF00;
	tmp->center = insert(-2, 0, 4);
	return (sphere);
}

int			main(void)
{
	t_cam		*o;
	t_view		*d;
	t_sphere	*sphere;
	int			x;
	int			y;
	int 		color;
	t_sdl		*sdl;


	sdl = (t_sdl *)ft_memalloc((sizeof(t_sdl)));
	sdl_init(sdl);

	//парсер чтобы считать сферы из файла в *shpere
	o = (t_cam *)ft_memalloc(sizeof(t_cam));
	o->position = (t_pos *)ft_memalloc(sizeof(t_pos));
	d = (t_view *)ft_memalloc(sizeof(t_view));
//	d->position = (t_pos *)ft_memalloc(sizeof(t_pos));

	o->position = insert(0, 0, 0);
	x = -WIDTH / 2;
	sphere = NULL;
	sphere = init_sphere(sphere);
	while(x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while(y < HEIGHT / 2)
		{
			d->position = (t_pos *)ft_memalloc(sizeof(t_pos));
			d->position = CanvasToViewport(x, y, d->position);
//			printf("%f %f %f\n", d->position->x, d->position->y, d->position->z);
			color = TraceRay(o, d, 1.0, INFINITY, sphere);
			sdl->pixels = put_pixel(x, y, color, sdl);
			y++;
		}
		x++;
	}
	sdl_control(sdl);
	return (0);
}