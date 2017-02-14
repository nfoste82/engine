#include "Vector3.h"
#include "Matrix3.h"

#include <sstream>

const Matrix3 Matrix3::Identity(Vector3::Right, Vector3::Up, Vector3::Forward);

Matrix3::Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2)
{
    SetRow(0, row0);
    SetRow(1, row1);
    SetRow(2, row2);
}

void Matrix3::SetRow(int rowIndex, const Vector3& row)
{
    // TODO: Range-checking in debug-only mode.
    
    m_values[0][rowIndex] = row.x;
    m_values[1][rowIndex] = row.y;
    m_values[2][rowIndex] = row.z;
}

Vector3 Matrix3::GetRow(int rowIndex) const
{
    return Vector3(m_values[0][rowIndex], m_values[1][rowIndex], m_values[2][rowIndex]);
}

Vector3 Matrix3::GetPitchAxis() const
{
    return GetRow(0);
}

Vector3 Matrix3::GetYawAxis() const
{
    return GetRow(1);
}

Vector3 Matrix3::GetRollAxis() const
{
    return GetRow(2);
}

float Matrix3::GetTrace() const
{
    return m_values[0][0] + m_values[1][1] + m_values[2][2];
}

std::ostream& operator<<(std::ostream& ofs, const Matrix3& rhs)
{
    std::stringstream stream;
    stream << rhs.GetRow(0) << std::endl
    << rhs.GetRow(1) << std::endl
    << rhs.GetRow(2);
    
    ofs.write(const_cast<char*>(stream.str().c_str()),
             static_cast<std::streamsize>(stream.str().size() *
                                          sizeof(char)) );
    
    return ofs;
}