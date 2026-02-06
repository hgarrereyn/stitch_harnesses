#include <iostream>
#include "autil/StringUtil.h"

int main() {
    std::string s = autil::StringUtil::toString(12345);
    std::vector<int> v = {1,2,3};
    std::string sv = autil::StringUtil::toString(v);
    autil::StringUtil::toLowerCase(s);
    std::cout << "s=" << s << ", v=" << sv << std::endl;
    return 0;
}
