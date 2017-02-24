#ifndef MATRIX3_H
#define MATRIX3_H

#include <ostream>

class Quaternion;
class Vector3;

class Matrix3
{
public:
    Matrix3() {}
    Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);
    
    static Matrix3 FromEulerAngles(float x, float y, float z);
    static Matrix3 FromQuaternion(const Quaternion& quat);
    
    void SetRow(int rowIndex, const Vector3& row);
    Vector3 GetRow(int rowIndex) const;
    
    Vector3 GetColumn(int columnIndex) const;
    
    Vector3 GetPitchAxis() const;
    Vector3 GetYawAxis() const;
    Vector3 GetRollAxis() const;
    
    inline float GetValue(int x, int y) const { return m_values[x][y]; }
    
    inline void SetValue(int x, int y, float value) { m_values[x][y] = value; }
    
    float GetTrace() const;
    
    Matrix3 Transpose() const;
    
    bool Inverse(Matrix3& invMat) const;

    static const Matrix3 Identity;
    
    Matrix3 operator*(const Matrix3& mat) const;
    
    friend std::ostream& operator<<(std::ostream& ofs, const Matrix3& rhs);
    
private:
    float m_values[3][3];
};

#endif // MATRIX3_H
