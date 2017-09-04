Optimizations

Use static array instead of std::vector to store points in Vec3 class
It was pretty silly to use std::vector, since its dynamically allocated.
I discovered this mistake when I looked at the callgrind output and saw millions of alloc calls.
Using a static array reduced the rendering time by 96%.

Use more aggressive compiler optimizations, such as the -Ofast flag.
This also significantly reduced the render time.

Inline frequently used functions.
This reduced render time by about 25%. The most challenging part of this
process was implementing Hitable Objects as a tagged union (using std::variant)

Next step: implement a bounding volume hierarchy to reduce # of intersect function calls
