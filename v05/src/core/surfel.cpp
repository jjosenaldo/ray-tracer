#include "surfel.h"

void Surfel::copy_from(const Surfel* other) {
    if (!other) return;
    
    p = other->p;
    n = other->n;
    wo = other->wo;
    time = other->time;
    uv = other->uv;
    primitive = other->primitive;
}