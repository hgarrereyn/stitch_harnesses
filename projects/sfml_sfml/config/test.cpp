#include <SFML/System.hpp>
#include <iostream>

int main() {
    sf::Clock clock;
    sf::String hello = U"Hello SFML System";
    sf::sleep(sf::milliseconds(10));
    sf::Time elapsed = clock.getElapsedTime();
    std::cout << "Message: " << hello.toAnsiString() << "\n";
    std::cout << "Elapsed: " << elapsed.asMicroseconds() << " us\n";
    // Use a couple of vector utilities
    sf::Vector2i a{3, 4};
    sf::Vector2i b{1, 2};
    auto c = a + b;
    std::cout << "Vector sum: (" << c.x << ", " << c.y << ")\n";
    return 0;
}
