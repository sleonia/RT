#include "rtv1.h"

t_result    intersect_ray_cylinder(t_pos *o, t_pos *d, t_cylinder *cyl)
{
    t_result    res;
    t_pos oc;
    double  a;
    double  b;
    double  c;
    double  discr;

    oc = vector_minus(o, &cyl->center);
    a = dot(d,d) - dot(d,&cyl->axis) * dot(d,&cyl->axis);
    c = dot(&oc,&oc) - dot(&oc,&cyl->axis) * dot(&oc,&cyl->axis) - cyl->radius * cyl->radius;
    b = dot(d,&oc) - dot(d,&cyl->axis) * dot(&oc,&cyl->axis);
    discr = b*b - a*c;
    if (discr < 0.0 )
    {
        res.t1 = INFINITY;
        res.t2 = INFINITY;
    }
    else
    {
        res.t1 = (-b - sqrt(discr))/(a);
        res.t2 = (-b + sqrt(discr))/(a);
    }
    return (res);
}