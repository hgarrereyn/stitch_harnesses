#include <iostream>
#include <vector>
#include <string>
#include <msgpack.hpp>

int main() {
    // Pack a simple vector of ints
    std::vector<int> v = {1, 2, 3, 4};
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, v);

    // Unpack it back
    msgpack::object_handle oh = msgpack::unpack(sbuf.data(), sbuf.size());
    msgpack::object deserialized = oh.get();

    // Convert to vector<int>
    std::vector<int> out;
    deserialized.convert(out);

    // Print sum to ensure it ran
    int sum = 0; for (int x : out) sum += x;
    std::cout << "sum=" << sum << " size=" << out.size() << "\n";
    return 0;
}
