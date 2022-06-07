#ifndef SURFEL_H
#define SURFEL_H

#include "vec3.h"
#include "primitive.h"

class Surfel {
    public:
        Point3f p;        //!< Contact point.
        Vector3f n;       //!< The surface normal.
        Vector3f wo;      //!< Outgoing direction of light, which is -ray.
        float time;       //!< Time of contact.
        Point2f uv;       //!< Parametric coordinate (u,v) of the hit surface.
        const Primitive *primitive = nullptr;   //!< Pointer to the primitive.
        
        Surfel( const Point3f& _p, const Vector3f& _n, const Vector3f& _wo, float _time,
                const Point2f& _uv, const Primitive *pri ) : p{_p}, n{_n}, wo{_wo},
                                                            time{_time}, uv{_uv}, primitive{pri} {/* empty */};
        Surfel() { }
};

#endif