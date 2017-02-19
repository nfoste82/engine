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

Matrix3 Matrix3::FromEulerAngles(float x, float y, float z)
{
    // Code in this method was referenced and adapted
    // from code written by Will Perone, located here:
    // https://github.com/MegaManSE/willperone/blob/master/Math/Matrix3.h
    
    float cx = cosf(x);
    float sx = sinf(x);
    float cy = cosf(y);
    float sy = sinf(y);
    float cz = cosf(z);
    float sz = sinf(z);
    float sxsy = sx * sy;
    float cxsy = cx * sy;
    
    Matrix3 mat;
    mat.SetValue(0, 0, cy * cz);
    mat.SetValue(1, 0, cy * sz);
    mat.SetValue(2, 0, -sy);
    
    mat.SetValue(0, 1, (sxsy * cz) - (cx * sz));
    mat.SetValue(1, 1, (sxsy * sz) + (cx * cz));
    mat.SetValue(2, 1, sx * cy);
    
    mat.SetValue(0, 2, (cxsy * cz) + (sx * sz));
    mat.SetValue(1, 2, (cxsy * sz) - (sx * cz));
    mat.SetValue(2, 2, cx * cy);
    return mat;
}

Vector3 Matrix3::GetRow(int rowIndex) const
{
    return Vector3(m_values[0][rowIndex], m_values[1][rowIndex], m_values[2][rowIndex]);
}

Vector3 Matrix3::GetColumn(int columnIndex) const
{
    return Vector3(m_values[columnIndex][0], m_values[columnIndex][1], m_values[columnIndex][2]);
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

// Gets the trace of the matrix (the diagonal)
float Matrix3::GetTrace() const
{
    return m_values[0][0] + m_values[1][1] + m_values[2][2];
}

// Gets a matrix that is the transposed version of this matrix.
// Transposed means that the rows become the columns, and vice versa.
Matrix3 Matrix3::Transpose() const
{
    Vector3 column0 = GetColumn(0);
    Vector3 column1 = GetColumn(1);
    Vector3 column2 = GetColumn(2);
    
    return Matrix3(column0, column1, column2);
}

// Returns true if an inverse matrix is created.
// Returns false if the determinant is zero or near zero.
bool Matrix3::Inverse(Matrix3& invMat) const
{
    // The longhand way of inverting a 3x3 matrix is pretty insane. It
    // includes finding a matrix of minors, then a cofactor matrix, then
    // find the determinant of the original, then multiply that determinant
    // with the transpose of the cofactor matrix (called an adjugate matrix),
    // and finally you have an inverse matrix.
    // Doing it the longhand way on a computer is wasteful and inefficient.
    // Through some tricks you can boil it down to far fewer operations, although
    // it's still not cheap!
    // The code below was taken from a Stack Overflow answer:
    // http://stackoverflow.com/a/18504573/967504
    // Although this formula can be found on other sites as well.
    
    double determinant =
    m_values[0][0] * (m_values[1][1] * m_values[2][2] - m_values[2][1] * m_values[1][2]) -
    m_values[0][1] * (m_values[1][0] * m_values[2][2] - m_values[1][2] * m_values[2][0]) +
    m_values[0][2] * (m_values[1][0] * m_values[2][1] - m_values[1][1] * m_values[2][0]);
    
    // If the determinant is near zero then we can't get an inverse determinant
    if (fabs(determinant) <= 0.00001f)
    {
        return false;
    }
    
    float invDet = 1 / (float)determinant;
    
    invMat.SetValue(0, 0, (m_values[1][1] * m_values[2][2] - m_values[2][1] * m_values[1][2]) * invDet);
    invMat.SetValue(0, 1, (m_values[0][2] * m_values[2][1] - m_values[0][1] * m_values[2][2]) * invDet);
    invMat.SetValue(0, 2, (m_values[0][1] * m_values[1][2] - m_values[0][2] * m_values[1][1]) * invDet);
    
    invMat.SetValue(1, 0, (m_values[1][2] * m_values[2][0] - m_values[1][0] * m_values[2][2]) * invDet);
    invMat.SetValue(1, 1, (m_values[0][0] * m_values[2][2] - m_values[0][2] * m_values[2][0]) * invDet);
    invMat.SetValue(1, 2, (m_values[1][0] * m_values[0][2] - m_values[0][0] * m_values[1][2]) * invDet);
    
    invMat.SetValue(2, 0, (m_values[1][0] * m_values[2][1] - m_values[2][0] * m_values[1][1]) * invDet);
    invMat.SetValue(2, 1, (m_values[2][0] * m_values[0][1] - m_values[0][0] * m_values[2][1]) * invDet);
    invMat.SetValue(2, 2, (m_values[0][0] * m_values[1][1] - m_values[1][0] * m_values[0][1]) * invDet);
    
    return true;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
    // 3x3 matrix multiplication in summary is:
    // * Multiply each row in Matrix A by each column in Matrix B
    //      * A Row 0 * B Column 0
    // out[0,0] = A[0,0] * B[0,0] + A[1,0] * B[0,1] + A[2,0] * B[0,2]
    //      * A Row 0 * B Column 1
    // out[0,1] ... etc ... etc
    
    Matrix3 outMat;
    outMat.SetValue(0, 0, GetRow(0).Dot(mat.GetColumn(0)));
    outMat.SetValue(0, 1, GetRow(0).Dot(mat.GetColumn(1)));
    outMat.SetValue(0, 2, GetRow(0).Dot(mat.GetColumn(2)));
    outMat.SetValue(1, 0, GetRow(1).Dot(mat.GetColumn(0)));
    outMat.SetValue(1, 1, GetRow(1).Dot(mat.GetColumn(1)));
    outMat.SetValue(1, 2, GetRow(1).Dot(mat.GetColumn(2)));
    outMat.SetValue(2, 0, GetRow(2).Dot(mat.GetColumn(0)));
    outMat.SetValue(2, 1, GetRow(2).Dot(mat.GetColumn(1)));
    outMat.SetValue(2, 2, GetRow(2).Dot(mat.GetColumn(2)));
    
    return outMat;
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