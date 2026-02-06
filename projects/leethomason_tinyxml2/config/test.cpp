#include <tinyxml2.h>
#include <iostream>

int main() {
    tinyxml2::XMLDocument doc;
    auto* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    auto* child = doc.NewElement("child");
    child->SetAttribute("name", "example");
    child->SetText("hello");
    root->InsertEndChild(child);

    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);
    // Output to ensure it runs
    std::cout << printer.CStr() << std::endl;
    return 0;
}
