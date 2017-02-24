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
    FromAxisAngle(axis, radians);
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

void Quaternion::FromAxisAngle(const Vector3& axis, float radians)
{
    float sn;
    Trig::SinCos(radians * 0.5f, sn, w);
    x = axis.x * sn;
    y = axis.y * sn;
    z = axis.z * sn;
}

// Note that this is non-const because if your quaternion is
// not-unit length then it must be unitized to prevent errors.
void Quaternion::ToAxisAngle(Vector3& axis, float& radians)
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

Quaternion Quaternion::FromEulerAngles(float x, float y, float z)
{
    // Code in this method was referenced and adapted
    // from code written by Will Perone, located here:
    // https://github.com/MegaManSE/willperone/blob/master/Math/quaternion.h
    
    float halfx = 0.5f * x;
    float halfy = 0.5f * y;
    float halfz = 0.5f * z;
    
    float cos_x_2 = cosf(halfx);
    float cos_y_2 = cosf(halfy);
    float cos_z_2 = cosf(halfz);
    
    float sin_x_2 = sinf(halfx);
    float sin_y_2 = sinf(halfy);
    float sin_z_2 = sinf(halfz);
    
    float czcy2 = cos_z_2 * cos_y_2;
    float szsy2 = sin_z_2 * sin_y_2;
    
    Quaternion q;
    q.w = (czcy2 * cos_x_2) + (szsy2 * sin_x_2);
    q.x = (czcy2 * sin_x_2) - (szsy2 * cos_x_2);
    q.y = (cos_z_2 * sin_y_2 * cos_x_2) + (sin_z_2 * cos_y_2 * sin_x_2);
    q.z = (sin_z_2 * cos_y_2 * cos_x_2) - (cos_z_2 * sin_y_2 * sin_x_2);
    return q;
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
    return (q1 * (1.0f - t) + q2 * t).Unitize();
}

// More accurate than Nlerp, but also more expensive.
// In my tests this is about 2-3x more expensive, but that will vary
// based on your hardware. Also, even though it's 2-3x more expensive,
// on my 3 year old MacBook Pro it still did 10000 calls in 1.7ms on a DEBUG build,
// and 0.473ms in RELEASE.
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
    if (dot < 0.0f)
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

// Works similar to Lerp, but always chooses the shortest rotation path.
Quaternion Quaternion::Nlerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    Quaternion result;
    float dot = q1.Dot(q2);
    float inverseT = 1.0f - t;
    
    if (dot < 0.0f)
    {
        t = -t;
    }
    
    // Lerp between q1 and q2. We can't just
    // call Lerp(), because inverseT is calculated
    // prior to the dot product check, and t
    // may have been changed.
    
    result.w = q1.w * inverseT + q2.w * t;
    result.x = q1.x * inverseT + q2.x * t;
    result.y = q1.y * inverseT + q2.y * t;
    result.z = q1.z * inverseT + q2.z * t;
    
    return result.Unitize();
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