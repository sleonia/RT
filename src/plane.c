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
    double  t;
    t_pos   oc;
    t_pos   min;
    t_result res;

    oc = vector_minus(cam,&pl->center);
    min = vector_on_number(&oc,-1);
    t = dot(&min,&pl->normal) / dot(view,&pl->normal);
    res.t1 = t;
    res.t2 = INFINITY;
    return (res); 
}