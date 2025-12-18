#include <cmath>

class Degrees;

class Radians {
private:
    float rad;
    static constexpr float EPS = 1e-5f;

public:
    
    Radians();
    Radians(float r);
    Radians(const Degrees& deg);

    
    Radians& operator+=(const Radians& other);
    Radians& operator-=(const Radians& other);
    friend Radians operator+(Radians lhs, const Radians& rhs);
    friend Radians operator-(Radians lhs, const Radians& rhs);

    float ToFloat() const;

    bool operator==(const Radians& other) const;
    bool operator!=(const Radians& other) const;
    bool operator<(const Radians& other) const;
    bool operator<=(const Radians& other) const;
    bool operator>(const Radians& other) const;
    bool operator>=(const Radians& other) const;

    Degrees ToDegrees() const;

};