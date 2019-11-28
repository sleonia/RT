#include "rtv1.h"

// t_plane init_plane()
// {
//     t_plane pl;

//     pl.normal.x = 1;
//     pl.normal.y = 3;
//     pl.normal.z = 2;
//     pl.center.x = 2;
//     pl.center.y = 3;
//     pl.center.z = 4;
//     return (pl);
// }


// /* валидация координат плоскости*/
// int check_plane(t_plane *pl)
// {
//     t_plane *pl1;
//     t_plane *tmp;

//     pl1 = pl;
//     while (pl1 != NULL)
//     {
//         if (pl->normal.x == pl->normal.y == pl->normal.z == 0 || 
//         (pl->normal.x == pl->center.x && pl->normal.y == pl->center.y && pl->normal.z == pl->center.z))
//         {
//             write(1, "Error a,b,c = 0 or norm == cent\n", 1);
//             //free;
//             exit(0); // or return (0);
//         }
//         else 
//         {
//             pl1 = tmp;
//         }
//     }
//     return (1);
// }

/*провеяет, лежит ли точка в плоскости*/
t_result intersect_ray_plane(t_pos *cam, t_pos *view, t_plane *pl) //view - точка экрана
{
    double  a;
    double  b;
    double  c;
    double  d;
    double  t;
    t_pos   i; // точка пересечения луча, выходящего из камеры и проходящего через плоскость проектирования, с плоскосьтю
    t_result res;

    a = pl->normal.x;
    b = pl->normal.y;
    c = pl->normal.z;
    d = -(a * pl->center.x + b * pl->center.y + c * pl->center.z);
    t = (a * cam->x + b * cam->y + c * cam->z + d) / 
        (a * cam->x - a * view->x + b * cam->y - b * view->y + 
        c * cam->z - c * view->z);
    // i.x = (1 - t) * cam->x + t * view->x;
    // i.y = (1 - t) * cam->y + t * view->y;
    // i.z = (1 - t) * cam->z + t * view->z; //проверка координат (?)
    // if (t >= 0 || (a * i.x + b * i.y + c * i.z + d != 0)) // (???) t может быть от 0 до +беск или от 0 до 1?
    // {
    //     t = INFINITY;
    // }
    res.t1 = t;
    res.t2 = INFINITY;
    return (res); 
}