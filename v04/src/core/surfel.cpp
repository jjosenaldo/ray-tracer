#include "surfel.h"

void Surfel::copy_from(Surfel* other) {
    p = other->p;
    n = other->n;
    wo = other->wo;
    time = other->time;
    uv = other->uv;
    primitive = other->primitive;
}