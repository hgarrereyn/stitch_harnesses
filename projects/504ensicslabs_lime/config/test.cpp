#include <iostream>
#include <lime_api.h>
int main(){
    std::cout << "Project: " << lime_project_name() << "\n";
    std::cout << "Magic: 0x" << std::hex << lime_magic() << std::dec << "\n";
    std::cout << "Version: " << lime_version_major() << "." << lime_version_minor() << "\n";
    return 0;
}
