#include <iostream>
#include <libprotobuf-mutator/src/mutator.h>
#include <google/protobuf/descriptor.pb.h>

int main() {
    // Use a well-known protobuf message type from libprotobuf itself.
    google::protobuf::DescriptorProto msg; // from google/protobuf/descriptor.pb.h
    msg.set_name("ExampleMessage");

    protobuf_mutator::Mutator m;
    m.Seed(1234);
    m.Mutate(&msg, 1024);

    // Serialize to ensure protobuf runtime is linked and functional.
    std::string out;
    if (!msg.SerializeToString(&out)) {
        std::cerr << "Serialization failed" << std::endl;
        return 1;
    }
    std::cout << "Mutated DescriptorProto size: " << out.size() << std::endl;
    return 0;
}
