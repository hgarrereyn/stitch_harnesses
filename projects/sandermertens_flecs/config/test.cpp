#include <flecs.h>
#include <iostream>

struct Position { float x, y; };
struct Velocity { float x, y; };

int main() {
    flecs::world ecs;

    ecs.system<Position, const Velocity>()
        .each([](Position& p, const Velocity& v) {
            p.x += v.x;
            p.y += v.y;
        });

    auto e = ecs.entity()
        .insert([](Position& p, Velocity& v) { p = {10, 20}; v = {1, 2}; });

    // Run a few frames
    for (int i = 0; i < 3; i++) { ecs.progress(); }

    const Position& p = e.get<Position>();
    std::cout << "Position: " << p.x << ", " << p.y << std::endl;
    return 0;
}
