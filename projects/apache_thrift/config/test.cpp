#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/TOutput.h>
#include <memory>
#include <iostream>
#include <string>

using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

int main() {
    // Create an in-memory buffer and a binary protocol
    std::shared_ptr<TMemoryBuffer> buffer = std::make_shared<TMemoryBuffer>();
    std::shared_ptr<TBinaryProtocol> proto = std::make_shared<TBinaryProtocol>(buffer);

    // Write some primitive values
    proto->writeI32(123456789);
    std::string msg = "hello thrift";
    proto->writeString(msg);

    // Inspect the serialized buffer
    uint8_t* data = nullptr;
    uint32_t size = 0;
    buffer->getBuffer(&data, &size);

    // Print size to verify it worked
    std::cout << "Serialized size: " << size << " bytes" << std::endl;
    return 0;
}
