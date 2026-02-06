#include <iostream>
#include "lgraph/base64_encode.h"

int main(){
    std::string in = "TuGraph";
    std::string enc = lgraph_api::base64::Encode(in);
    std::string dec = lgraph_api::base64::Decode(enc);
    std::cout << enc << " " << dec << "\n";
    return 0;
}
