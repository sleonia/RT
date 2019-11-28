#include "rtv1.h"

t_result    intersect_ray_cone(t_pos *o, t_pos *d, t_cone *cone)
{
    t_result    res;
    t_pos oc;
    double  a;
    double  b;
    double  c;
    double  discr;

    oc = vector_minus(o, &cone->center);
    a = dot(d,d) - (1 + cone->tan * cone->tan)*dot(d,&cone->axis) * dot(d,&cone->axis);
    c = dot(&oc,&oc) - (1 + cone->tan * cone->tan)*dot(&oc,&cone->axis) * dot(&oc,&cone->axis);
    b = dot(d,&oc) - (1 + cone->tan * cone->tan)*dot(d,&cone->axis) * dot(&oc,&cone->axis);
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