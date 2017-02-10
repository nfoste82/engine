#include "Vector3.h"

#include <sstream>

const Vector3 Vector3::Right(1.f, 0.f, 0.f);
const Vector3 Vector3::Up(0.f, 1.f, 0.f);
const Vector3 Vector3::Forward(0.f, 0.f, 1.f);
const Vector3 Vector3::Left(-1.f, 0.f, 0.f);
const Vector3 Vector3::Down(0.f, -1.f, 0.f);
const Vector3 Vector3::Backward(0.f, 0.f, -1.f);

const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

Vector3::Vector3() :
    x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3::Vector3(const float _x, const float _y, const float _z) :
    x(_x), y(_y), z(_z)
{
}

// Copy constructor
Vector3::Vector3(const Vector3& rhs) :
    x(rhs.x), y(rhs.y), z(rhs.z)
{
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

void Vector3::operator+=(const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

void Vector3::operator-=(const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}

void Vector3::operator*=(const int scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

void Vector3::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

Vector3 operator*(const Vector3& vector, const int scalar)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3 operator*(const Vector3& vector, const float scalar)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3 operator*(const int scalar, const Vector3& vector)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3 operator*(const float scalar, const Vector3& vector)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

std::ostream& operator<< (std::ostream& os, const Vector3& vector)
{
    std::stringstream stream;
    stream << "X: " << vector.x << ", Y: " << vector.y << ", Z: " << vector.z;
    os.write(const_cast<char*>(stream.str().c_str()),
             static_cast<std::streamsize>(stream.str().size() *
             sizeof(char)) );
    
    return os;
}

Vector3 Vector3::Cross(const Vector3& rhs) const
{
    return Vector3( (y * rhs.z) - (z * rhs.y),
                    (z * rhs.x) - (x * rhs.z),
                    (x * rhs.y) - (y * rhs.x) );
}

float Vector3::Unitize()
{
    const float length = Length();
    const float inverseLength = 1.0f / length;
    x *= inverseLength;
    y *= inverseLength;
    z *= inverseLength;
    return length;
}

void Vector3::Reflect(const Vector3& normal)
{
    const float dotProductTimesTwo = Dot(normal) * 2.0f;
    x -= dotProductTimesTwo * normal.x;
    y -= dotProductTimesTwo * normal.y;
    z -= dotProductTimesTwo * normal.z;
}

Vector3 Vector3::Reflect(const Vector3& vector, const Vector3& normal)
{
    Vector3 newVector;
    const float dotProductTimesTwo = vector.Dot(normal) * 2.0f;
    newVector.x = vector.x - (dotProductTimesTwo * normal.x);
    newVector.y = vector.y - (dotProductTimesTwo * normal.y);
    newVector.z = vector.z - (dotProductTimesTwo * normal.z);
    return newVector;
}

Vector3 Vector3::GetLongest(const Vector3& first, const Vector3& second)
{
    if (first.LengthSqr() > second.LengthSqr())
    {
        return first;
    }

    return second;
}