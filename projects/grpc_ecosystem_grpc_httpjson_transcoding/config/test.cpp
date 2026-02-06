#include <iostream>
#include "grpc_transcoding/http_template.h"

int main() {
    std::unique_ptr<google::grpc::transcoding::HttpTemplate> t = google::grpc::transcoding::HttpTemplate::Parse("/v1/books/{book}/pages/{page}:read");
    if (!t) {
        std::cout << "Parse failed\n";
        return 0;
    }
    std::cout << "Segments: " << t->segments().size() << ", Verb: " << t->verb() << "\n";
    return 0;
}
