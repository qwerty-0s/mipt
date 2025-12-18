#include <cmath>

class Radians;

class Degrees{
private:
    int degrees;
    int minutes;
    int seconds;
    float eps = 1e-5f;

public:
    Degrees(int degrees_, int minutes_, int seconds_);
    Degrees(const Radians& rad);

    Degrees& operator += (const Degrees& other);
    Degrees& operator -= (const Degrees& other);
    friend Degrees operator+ (Degrees lhs, const Degrees& rhs);
    friend Degrees operator- (Degrees lhs, const Degrees& rhs);

    float ToFloat() const;

    bool operator ==(const Degrees& other) const;
    bool operator !=(const Degrees& other) const;
    bool operator >=(const Degrees& other) const;
    bool operator <=(const Degrees& other) const;
    bool operator >(const Degrees& other) const;
    bool operator <(const Degrees& other) const;

    Radians ToRadians() const;

    void Normalize();

};