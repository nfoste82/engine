#ifndef MATRIX3_H
#define MATRIX3_H

#include <ostream>

class Vector3;

class Matrix3
{
public:
    Matrix3(const Vector3& row0, const Vector3& row1, const Vector3& row2);
    
    void SetRow(int rowIndex, const Vector3& row);
    Vector3 GetRow(int rowIndex) const;
    
    Vector3 GetPitchAxis() const;
    Vector3 GetYawAxis() const;
    Vector3 GetRollAxis() const;
    
    inline float GetValue(int x, int y) const { return m_values[x][y]; }
    
    float GetTrace() const;

    static const Matrix3 Identity;
    
    friend std::ostream& operator<<(std::ostream& ofs, const Matrix3& rhs);
    
public:
    // These are public for pure performance reasons. But allowing
    // public access to these could easily cause problems.
    // Consider inline accessors to read these.
    float m_values[3][3];
};

#endif // MATRIX3_H
