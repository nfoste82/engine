#include "Matrix3.h"

float Matrix3::GetTrace() const
{
    return m_values[0][0] + m_values[1][1] + m_values[2][2];
}