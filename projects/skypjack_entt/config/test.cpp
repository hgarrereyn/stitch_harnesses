#include <entt/entt.hpp>
#include <iostream>

struct position { float x, y; };
struct velocity { float dx, dy; };

int main() {
    entt::registry reg;

    for(unsigned i = 0; i < 6; ++i) {
        auto e = reg.create();
        reg.emplace<position>(e, float(i), float(i));
        if(i % 2 == 0) {
            reg.emplace<velocity>(e, 0.1f * i, 0.2f * i);
        }
    }

    std::size_t count = 0;
    auto view = reg.view<const position, entt::exclude_t<>>();
    for(auto [entity, pos] : view.each()) {
        (void)entity;
        if(pos.x == pos.y) { ++count; }
    }

    std::cout << "Entities with position: " << count << "\n";
    return 0;
}
