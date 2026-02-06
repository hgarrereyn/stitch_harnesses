#include <drogon/HttpResponse.h>
#include <drogon/HttpRequest.h>
#include <drogon/drogon.h>
#include <iostream>

int main() {
    using namespace drogon;
    // Create a simple HTTP response without starting the server
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("<p>Hello from Drogon test!</p>");

    // Create a simple HTTP request and attach attributes
    auto req = HttpRequest::newHttpRequest();
    req->addHeader("X-Test", "1");

    // Use a small utility from drogon
    std::string_view body_sv = resp->getBody();
    std::cout << "Body size: " << body_sv.size() << "\n";
    std::cout << "Header X-Test present? " << (req->getHeader("X-Test").empty() ? "no" : "yes") << "\n";

    return 0;
}
