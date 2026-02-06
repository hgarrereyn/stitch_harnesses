#include <znc/ZNCString.h>
#include <iostream>

int main() {
    CString a("12345");
    int value = 0;
    bool ok = a.Convert(&value);
    std::cout << "Converted: " << (ok ? "true" : "false") << ", value=" << value << "\n";
    CString delim(",");
    std::vector<int> nums = {1,2,3};
    CString joined = delim.Join(nums.begin(), nums.end());
    std::cout << "Joined: " << std::string(joined) << "\n";
    return 0;
}
