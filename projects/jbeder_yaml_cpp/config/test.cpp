#include <yaml-cpp/yaml.h>
#include <iostream>
#include <sstream>

int main() {
    // Simple YAML string
    const std::string input = "name: yaml-cpp\nversion: 0.8\nfeatures:\n  - parse\n  - emit\n";

    YAML::Node root = YAML::Load(input);
    if (!root || !root["name"]) {
        std::cout << "Failed to parse" << std::endl;
        return 1;
    }

    std::string name = root["name"].as<std::string>("unknown");

    // Emit a small YAML document
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "project" << YAML::Value << name;
    out << YAML::Key << "feature_count" << YAML::Value << root["features"].size();
    out << YAML::EndMap;

    std::cout << out.c_str() << std::endl;
    return 0;
}
