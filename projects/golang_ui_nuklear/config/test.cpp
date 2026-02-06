#include <iostream>
#include <nuklear.h>

int main() {
    struct nk_rect r = nk_rect(1.0f, 2.0f, 3.0f, 4.0f);
    struct nk_vec2 v = nk_vec2(5.0f, 6.0f);
    std::cout << "rect: (" << r.x << ", " << r.y << ", " << r.w << ", " << r.h << ")\n";
    std::cout << "vec2: (" << v.x << ", " << v.y << ")\n";
    return 0;
}
