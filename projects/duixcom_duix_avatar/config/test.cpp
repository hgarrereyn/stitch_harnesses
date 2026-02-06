#include <iostream>
#include <cstring>
extern "C" {
#include <duix_avatar.h>
}
int main(){
    std::cout << "Duix.Avatar stub version: " << duix_avatar_version() << "\n";
    const char* msg = duix_avatar_hello();
    if(msg && std::strlen(msg)>0){
        std::cout << "Message: " << msg << "\n";
    }
    return 0;
}
