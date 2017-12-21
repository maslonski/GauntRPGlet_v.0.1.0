#ifndef FLOAT2_H
#define FLOAT2_H

#include <math.h>

struct float2
{
    float x, y;
    float2(): x(0), y(0) {}
    float2(float _x, float _y): x(_x), y(_y) {}
    float2(float angle) // konstruuje wektor z kata
        :x(cos(angle*0.01745f)), y(sin(angle*0.01745f)) {}

    float2 operator*(float f) { return float2(x*f, y*f); }
    float2 &operator+=(float2 f) { x+=f.x; y+=f.y; return *this; }
    float2 &operator-=(float2 f) { x-=f.x; y-=f.y; return *this; }

    float2 operator+(float2 f) { return float2(x+f.x, y+f.y); }
    float2 operator-(float2 f) { return float2(x-f.x, y-f.y); }

    float2 normalized()
    {
        if (fabs(x)<.001f && fabs(y)<.001f)
            return float2(0.f, 0.f);
        else
            return *this/sqrt(x*x+y*y);
    }

    float2 operator/(float f) { return float2(x/f, y/f); }

    void clampLen(float f)
    {
        if (fabs(x)<.001f && fabs(y)<.001f)
            return;
        float len = sqrt(x*x+y*y);
        if (len > f)
        {
            x *= f/len;
            y *= f/len;
        }
    }
    float len()
    {
        return sqrt(x*x+y*y);
    }
    float toAngle()
    {
        return atan2(y, x) * 57.2957795f;
    }

    float skalar(float2 _tmp)
    {
    	return (this->x * _tmp.x + this->y * _tmp.y);
    }

    void zero() { x=y=0.f; }
    bool isZero() { return x==0.f && y==0.f; }
};

#endif // FLOAT2_H
