//===============================================================================
//
// Quaternion math for q1*q2 and quat*rot-mat were referenced from a whitepaper:
// Quaternions, Ken Shoemake
// Department of Computer and Information Science
// University of Pennsylvania
// http://www.cs.ucr.edu/~vbz/resources/quatut.pdf
//
// For Quaternion to angle/axis:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/
//
// For Quaternion from angle/axis:
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/
//===============================================================================

#include <math.h>
#include <sstream>
#include "Matrix3.h"
#include "Trig.h"
#include "Vector3.h"
#include "Quaternion.h"

Quaternion::Quaternion(float _w, float _x, float _y, float _z) :
    w(_w), x(_x), y(_y), z(_z)
{
}

Quaternion::Quaternion(float radians, const Vector3& axis)
{
    FromAngleAxis(radians, axis);
}

const Quaternion& Quaternion::Unitize()
{
    float length = w * w + x * x + y * y + z * z;
    
    // We don't need a division operator overload, we can just
    // invert here and then multiply.
    float inverseLength = 1.0f / sqrt(length);
    w *= inverseLength;
    x *= inverseLength;
    y *= inverseLength;
    z *= inverseLength;
    
    return *this;
}

Quaternion Quaternion::GetUnitized() const
{
    float length = w * w + x * x + y * y + z * z;

    float inverseLength = 1.0f / sqrt(length);

    return Quaternion(w * inverseLength, x * inverseLength,
                      y * inverseLength, z * inverseLength);
}

void Quaternion::FromAngleAxis(float radians, const Vector3& axis)
{
    float sn;
    Trig::SinCos(radians * 0.5f, sn, w);
    x = axis.x * sn;
    y = axis.y * sn;
    z = axis.z * sn;
}

// Note that this is non-const because if your quaternion is
// not-unit length then it must be unitized to prevent errors.
void Quaternion::ToAngleAxis(float& radians, Vector3& axis)
{
    if (w > 1)
    {
        Unitize();
    }
    
    float length = sqrtf(1 - w * w);
    
    // If the length is less than epsilon then the quaternion
    // is invalid so we just return zeros. Without this check
    // we would end up with essentially a divide by zero and
    // the resulting axis would be extremely large. Acos(w) may crash in this case
    // as well.
    
    if (length < Epsilon)
    {
        radians = 0;
        axis.x = 0;
        axis.y = 0;
        axis.z = 0;
    }
    else
    {
        // It's faster to do a single division here to get the inverse length
        // than it is to divide the entire axis by length. 1 div and 3 muls is
        // generally cheaper than 3 divs.
        
        float inverseLength = 1.0f / length;
        axis.x = x * inverseLength;
        axis.y = y * inverseLength;
        axis.z = y * inverseLength;
        
        radians = 2.0f * acos(w);
    }
}

void Quaternion::FromRotationMatrix(const Matrix3& mat)
{
    float trace = mat.GetTrace();
    float sroot;
    
    if (trace > 0.0f)
    {
        // K.Shoemake's algorithm assumed a 4x4 matrix in several places, we can just use 1.0f where location 3,3 would've been.
        
        sroot = sqrt(trace + 1.0f);
        w = 0.5f * sroot;
        sroot = 0.5f / sroot;
        
        x = (mat.GetValue(2, 1) - mat.GetValue(1, 2)) * sroot;
        y = (mat.GetValue(0, 2) - mat.GetValue(2, 0)) * sroot;
        z = (mat.GetValue(1, 0) - mat.GetValue(0, 1)) * sroot;
    }
    else
    {
        // Ken Shoemake's algorithm used some funky macro code to
        // generate a set of values and a switch statement and pick one of the statements.
        // We can just use an array with those values and determine which data
        // from that array to use, allowing us to skip the macro stuff.
        
        static int switchValue[3] = {1, 2, 0};
        int i = 0;
        if (mat.GetValue(1, 1) > mat.GetValue(0, 0))
        {
            i = 1;
        }
        
        if (mat.GetValue(2, 2) > mat.GetValue(i, i))
        {
            i = 2;
        }
        
        int j = switchValue[i];
        int k = switchValue[j];
        
        sroot = sqrt(mat.GetValue(i, i) - mat.GetValue(j, j) - mat.GetValue(k, k) + 1.0f);
        
        SetValue(i, 0.5f * sroot);
        
        sroot = 0.5f / sroot;
        w = (mat.GetValue(k, j) - mat.GetValue(j, k)) * sroot;
        
        SetValue(j, (mat.GetValue(j, i) + mat.GetValue(i, j)) * sroot);
        SetValue(k, (mat.GetValue(k, i) + mat.GetValue(i, k)) * sroot);
    }
}

float Quaternion::Dot(const Quaternion& q) const
{
    return w * q.w + x * q.x + y * q.y + z * q.z;
}

Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    return (q1 * (1 - t) + q2 * t).Unitize();
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    Quaternion q3 = Quaternion::Identity;
    float dot = q1.Dot(q2);
    
    // The angle between the rotations is tiny, so we'll just lerp.
    if (dot > 0.995f)
    {
        return Lerp(q1, q3, t);
    }
    
    // Dot is cos(theta), when dot is less than 0 then the rotations are
    // more than 90 degrees apart from one another. We need to invert
    // one of the quaternions so we don't end up rotating more than 180 degrees.
    if (dot < 0.f)
    {
        float angle = acosf(-dot);
        return (q1 * sinf(angle * (1 - t)) + -q2 * sinf(angle * t)) / sinf(angle);
    }
    else
    {
        float angle = acosf(dot);
        return (q1 * sinf(angle * (1 - t)) + q2 * sinf(angle * t)) / sinf(angle);
    }
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
    return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
    return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    return Quaternion(w * q.w - x * q.x - y * q.y - z * q.z,
                      w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y + y * q.w + z * q.x - x * q.z,
                      w * q.z + z * q.w + x * q.y - y * q.x);
}

Quaternion Quaternion::operator*(float scalar) const
{
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}

Quaternion Quaternion::operator/(float scalar) const
{
    float inverse = 1 / scalar;
    return Quaternion(w * inverse, x * inverse, y * inverse, z * inverse);
}

Quaternion Quaternion::operator-() const
{
    return Quaternion(-w, -x, -y, -z);
}

void Quaternion::operator*=(const float scalar)
{
    w *= scalar;
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

std::ostream& operator<<(std::ostream& ofs, const Quaternion& rhs)
{
    std::stringstream stream;
    stream << "W: " << rhs.w << ", X: " << rhs.x << ", Y: " << rhs.y << ", Z: " << rhs.z;
    
    ofs.write(const_cast<char*>(stream.str().c_str()),
              static_cast<std::streamsize>(stream.str().size() *
                                           sizeof(char)) );
    
    return ofs;
}

float Quaternion::GetValue(int index) const
{
    switch (index)
    {
        case 0: return w;
        case 1: return x;
        case 2: return y;
        case 3: return z;
        default: break;
    }
    
    throw "Quaternion index out of range.";
}

void Quaternion::SetValue(int index, float value)
{
    switch (index)
    {
        case 0: w = value; return;
        case 1: x = value; return;
        case 2: y = value; return;
        case 3: z = value; return;
        default: break;
    }
    
    throw "Quaternion index out of range.";
}

const float Quaternion::Epsilon = 0.001f;
const Quaternion Quaternion::Identity(1.0f, 0.0f, 0.0f, 0.0f);