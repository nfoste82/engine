#include "Matrix3.h"

float Matrix3::GetTrace() const
{
    return m00 + m11 + m22;
}