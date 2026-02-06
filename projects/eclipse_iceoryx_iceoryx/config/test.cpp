#include <iostream>
#include "iceoryx_posh/iceoryx_posh_types.hpp"
#include "iceoryx_posh/capro/service_description.hpp"
#include "iceoryx_posh/popo/publisher_options.hpp"
#include "iceoryx_posh/popo/subscriber_options.hpp"

int main() {
    using namespace iox;

    capro::ServiceDescription svc{"TestService", "TestInstance", "TestEvent"};
    popo::PublisherOptions pubOptions; // default constructed
    popo::SubscriberOptions subOptions; // default constructed

    std::cout << "Service: " << svc.getServiceIDString().c_str() << "/"
              << svc.getInstanceIDString().c_str() << "/"
              << svc.getEventIDString().c_str() << std::endl;
    std::cout << "Publisher history capacity: " << pubOptions.historyCapacity << std::endl;
    std::cout << "Subscriber queue capacity: " << subOptions.queueCapacity << std::endl;

    return 0;
}
