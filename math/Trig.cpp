#include <math.h>
#include "Trig.hpp"

void Trig::SinCos(float x, float& sn, float& cs)
{
    sn = sinf(x);
    cs = cosf(x);
}
