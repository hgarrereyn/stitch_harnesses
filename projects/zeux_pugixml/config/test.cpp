#include <pugixml.hpp>
#include <iostream>

int main() {
    const char* xml = "<Profile><Tools><Tool Filename=\"gcc\" Timeout=\"5\"/><Tool Filename=\"clang\" Timeout=\"0\"/></Tools></Profile>";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml);
    if (!result) {
        std::cout << "Parse failed: " << result.description() << "\n";
        return 0;
    }

    int count = 0;
    for (pugi::xml_node tool: doc.child("Profile").child("Tools").children("Tool")) {
        int timeout = tool.attribute("Timeout").as_int();
        if (timeout > 0) {
            std::cout << "Tool " << tool.attribute("Filename").value() << " has timeout " << timeout << "\n";
            ++count;
        }
    }

    pugi::xpath_node_set nodes = doc.select_nodes("/Profile/Tools/Tool[@Timeout > 0]");
    std::cout << "XPath found: " << nodes.size() << " tool(s) with timeout > 0\n";
    std::cout << "Document child count: " << doc.child("Profile").child("Tools").select_nodes("Tool").size() << "\n";
    return 0;
}
