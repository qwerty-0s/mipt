#include <cmath> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "radians.h"
#include "degrees.h"


Radians::Radians()
{
    rad = 0.0f;
}
Radians::Radians(float rad_) 
{ 
    rad = rad_;
}

Radians::Radians(const Degrees& deg) 
{
    float totalDegrees = deg.ToFloat();
    rad = totalDegrees * static_cast<float>(M_PI) / 180.0f;
}

Radians& Radians::operator+=(const Radians& other) 
{
    rad += other.rad;
    return *this;
}

Radians& Radians::operator-=(const Radians& other) 
{
    rad -= other.rad;
    return *this;
}

Radians operator+(Radians lhs, const Radians& rhs) 
{
    lhs += rhs;
    return lhs;
}

Radians operator-(Radians lhs, const Radians& rhs) 
{
    lhs -= rhs;
    return lhs;
}


float Radians::ToFloat() const 
{
    return rad;
}


bool Radians::operator==(const Radians& other) const 
{
    return std::abs(rad - other.rad) < EPS;
}

bool Radians::operator!=(const Radians& other) const 
{
    return !(*this == other);
}

bool Radians::operator<(const Radians& other) const 
{
    return rad < other.rad - EPS;
}

bool Radians::operator<=(const Radians& other) const 
{
    return rad < other.rad + EPS;
}

bool Radians::operator>(const Radians& other) const 
{
    return rad > other.rad + EPS;
}

bool Radians::operator>=(const Radians& other) const 
{
    return rad > other.rad - EPS;
}

Degrees Radians::ToDegrees() const {
    float totalDegrees = rad * 180.0f / static_cast<float>(M_PI);
    int d = static_cast<int>(totalDegrees);
    float frac = (totalDegrees - d) * 60.0f;
    int m = static_cast<int>(frac);
    int s = static_cast<int>((frac - m) * 60.0f);
    return Degrees(d, m, s);
}

Degrees::Degrees(int degrees_, int minutes_, int seconds_)
{
    int totalSeconds = degrees_ * 3600 + minutes_ * 60 + seconds_;
    degrees = totalSeconds / 3600;
    totalSeconds %= 3600;
    minutes = totalSeconds / 60;
    seconds = totalSeconds % 60;
}

Degrees::Degrees(const Radians& r) {
    float totalDegrees = r.ToFloat() * 180.0f / static_cast<float>(M_PI);
    degrees = static_cast<int>(totalDegrees);
    float frac = (totalDegrees - degrees) * 60.0f;
    minutes = static_cast<int>(frac);
    seconds = static_cast<int>((frac - minutes) * 60.0f);
    Normalize();
}

Degrees& Degrees::operator+=(const Degrees& other)
{
    seconds += other.seconds; 
    minutes += other.minutes + seconds/60;
    seconds %=60;

    degrees += other.degrees + minutes/60;
    minutes %=60;
    Normalize();

    return *this;  
}

Degrees& Degrees::operator-=(const Degrees& other)
{
    
    seconds -= other.seconds;
    minutes -= other.minutes;
    degrees -= other.degrees;

    Normalize();

    return *this;
}

Degrees operator+(Degrees lhs, const Degrees& rhs)
{
    lhs += rhs;
    return lhs;
}

Degrees operator-(Degrees lhs, const Degrees& rhs)
{
    lhs -= rhs;
    return lhs;
}

float Degrees::ToFloat() const
{
    float total = degrees + minutes / 60.0f + seconds / 3600.0f;
    return total;
}

bool Degrees::operator==(const Degrees& other) const
{
    return std::abs(ToFloat() - other.ToFloat()) < eps;
}
bool Degrees::operator!=(const Degrees& other) const
{
    return std::abs(ToFloat() - other.ToFloat()) > eps;
}
bool Degrees::operator>=(const Degrees& other) const
{
    return ToFloat() > other.ToFloat() - eps;
}
bool Degrees::operator<=(const Degrees& other) const
{
    return ToFloat() < other.ToFloat() + eps;
}
bool Degrees::operator>(const Degrees& other) const
{
    return ToFloat() > other.ToFloat() + eps;
}
bool Degrees::operator<(const Degrees& other) const
{
    return ToFloat() < other.ToFloat() - eps;
}


Radians Degrees::ToRadians() const {
    float totalDegrees = ToFloat();
    return Radians(totalDegrees * static_cast<float>(M_PI) / 180.0f);
}

void Degrees::Normalize() {
    int total = degrees * 3600 + minutes * 60 + seconds;
    degrees = total / 3600;
    total %= 3600;
    minutes = total / 60;
    seconds = total % 60;
}