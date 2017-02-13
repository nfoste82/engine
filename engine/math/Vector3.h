#ifndef VECTOR_3
#define VECTOR_3

#include <math.h>
#include <ostream>

class Vector3
{
public:
    Vector3(void);
    explicit Vector3(float x, float y, float z);
    
    // Copy constructor
    Vector3(const Vector3& rhs);
    
    ~Vector3(void);
    
    bool operator==(const Vector3& rhs) const { return ( (x == rhs.x) && (y == rhs.y) && (z == rhs.z));}
    bool operator!=(const Vector3& rhs) const { return ( (x != rhs.x) || (y != rhs.y) || (z != rhs.z));}
    Vector3 operator+(const Vector3& rhs) const;
    void operator+=(const Vector3& rhs);
    Vector3 operator-(const Vector3& rhs) const;
    Vector3 operator-(void) const;
    void operator-=(const Vector3& rhs);
    void operator*=(const int scalar);
    void operator*=(const float scalar);
    
    // Non-member operators get a friend declaration
    friend Vector3 operator*(const Vector3& vector, const int scalar);
    friend Vector3 operator*(const Vector3& vector, float scalar);
    friend Vector3 operator*(const int scalar, const Vector3& vector);
    friend Vector3 operator*(const float scalar, const Vector3& vector);
    friend std::ostream& operator<<(std::ostream& ofs,const Vector3& rhs);
    
    inline void Flip(void) { x = -x; y = -y; z = -z; }
    
    inline float Dot(const Vector3& rhs) const { return (x * rhs.x + y * rhs.y + z * rhs.z); }
    
    Vector3 Cross(const Vector3& rhs) const;
    
    float Length(void) const { return sqrtf( LengthSqr() ); }
    
    inline float LengthSqr(void) const { return (x * x + y * y + z * z); }
    
    float Unitize(void);
    
    void Reflect( const Vector3& rhs );
    
    static Vector3 Reflect( const Vector3& first, const Vector3& second );
    static Vector3 GetLongest(const Vector3& first, const Vector3& second);
    
    static const Vector3 Left;
    static const Vector3 Right;
    static const Vector3 Up;
    static const Vector3 Down;
    static const Vector3 Forward;
    static const Vector3 Backward;
    
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
    
    static const Vector3 Zero;
    static const Vector3 One;
    
    float x;
    float y;
    float z;
};

#endif //VECTOR_3
