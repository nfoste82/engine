#include <math.h>
#include "Trig.h"

void Trig::SinCos(float x, float& sn, float& cs)
{
    sn = sinf(x);
    cs = cosf(x);
}