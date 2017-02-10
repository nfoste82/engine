#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
class Vector3;

class Quaternion
{
    Quaternion(float _w, float _x, float _y, float _z);
    
    Quaternion(float angleRadians, const Vector3& axis);
    
    void Unitize();
    Quaternion GetUnitized() const;
    
    void FromAngleAxis(float angle, const Vector3& axis);
    void ToAngleAxis(float& angle, Vector3& axis);
    
    void FromRotationMatrix(const Matrix3& rot);
    
    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator-() const;
    
    void operator*=(const float scalar);
    
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
