#ifndef MATRIX3_H
#define MATRIX3_H

class Matrix3
{
public:
    inline float GetValue(int x, int y) const { return m_values[x][y]; }
    
    float GetTrace() const;

public:
    // These are public for pure performance reasons. But allowing
    // public access to these could easily cause problems.
    // Consider inline accessors to read these.
    float m_values[3][3];
};

#endif // MATRIX3_H
