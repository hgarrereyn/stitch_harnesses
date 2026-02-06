#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <util/buffer.h>
#include <iostream>

int main() {
    using namespace isc::dhcp;
    using isc::util::OutputBuffer;

    OptionBuffer data; data.push_back('k'); data.push_back('e'); data.push_back('a');
    Option opt(Option::V4, 12, data);

    OutputBuffer buf(0);
    opt.pack(buf, true);

    std::cout << "Packed option size: " << buf.getLength() << "\n";
    return 0;
}
