#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>
#include <fastdds/dds/log/Log.hpp>

using namespace eprosima::fastdds::dds;

int main() {
    // Access the singleton to force linking against the library
    DomainParticipantFactory* factory = DomainParticipantFactory::get_instance();

    // Configure a participant QoS without actually creating any participant
    DomainParticipantQos qos;
    qos.name("fuzz_test_participant");

    // Set and get default QoS to exercise a tiny bit of code
    factory->set_default_participant_qos(qos);
    DomainParticipantQos roundtrip = factory->get_default_participant_qos();

    // Touch logging API
    eprosima::fastdds::dds::Log::SetVerbosity(eprosima::fastdds::dds::Log::Kind::Error);

    (void)roundtrip; // suppress unused warning
    return 0;
}
