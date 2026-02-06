#include <iostream>
#include "opencensus/common/version.h"
#include "opencensus/trace/span.h"

int main() {
    std::cout << "OpenCensus version: " << OPENCENSUS_VERSION << "\n";
    auto span = ::opencensus::trace::Span::StartSpan("test-span");
    span.AddAnnotation("hello");
    span.End();
    std::cout << "Span created and ended successfully." << std::endl;
    return 0;
}
