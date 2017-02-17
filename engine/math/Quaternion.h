#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
class Vector3;

class Quaternion
{
public:
    Quaternion() {}
    Quaternion(float _w, float _x, float _y, float _z);
    
    Quaternion(float angleRadians, const Vector3& axis);
    
    const Quaternion& Unitize();
    Quaternion GetUnitized() const;
    
    void FromAngleAxis(float angle, const Vector3& axis);
    void ToAngleAxis(float& angle, Vector3& axis);
    
    void FromRotationMatrix(const Matrix3& rot);
    
    float Dot(const Quaternion& q) const;
    static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
    static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
    
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float scalar) const;
    Quaternion operator/(float scalar) const;
    Quaternion operator-() const;
    
    void operator*=(const float scalar);
    
    friend std::ostream& operator<<(std::ostream& ofs,const Quaternion& rhs);
    
    float GetValue(int index) const;
    void SetValue(int index, float value);
    
    float w;
    float x;
    float y;
    float z;
    
    static const float Epsilon;
    static const Quaternion Identity;
};

#endif // QUATERNION_H
