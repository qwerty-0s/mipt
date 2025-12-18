#include <iostream>
#include "degrees.h"
#include "radians.h"

int main() {
    Degrees d1(30, 15, 0);
    Degrees d2(15, 45, 30);

    Radians r1(3.14159265f / 2); 
    Radians r2 = d1.ToRadians();

    Degrees d3 = d1 + d2;
    std::cout << "d1 + d2 = " << d3.ToFloat() << "°\n";

    d1 += d2;
    std::cout << "d1 after += d2: " << d1.ToFloat() << "°\n";

    Radians r3 = r1 + r2;
    std::cout << "r1 + r2 = " << r3.ToFloat() << " rad\n";

    Degrees d_from_r = r3.ToDegrees();
    std::cout << "r3 to degrees = " << d_from_r.ToFloat() << "°\n";

    Degrees d4(45, 60, 0); 
    std::cout << "d4 > d3? " << (d4 > d3 ? "true" : "false") << "\n";

    return 0;
}
