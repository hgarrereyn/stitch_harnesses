#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include <Plist.hpp>

int main() {
    using namespace Plist;

    dictionary_type dict;
    dict["name"] = string_type("OCAuxiliaryTools");
    dict["version"] = integer_type(1);
    dict["enabled"] = boolean_type(true);

    std::vector<char> xmlBuf;
    writePlistXML(xmlBuf, dict);

    boost::any parsed;
    readPlist(xmlBuf.data(), static_cast<int64_t>(xmlBuf.size()), parsed);

    if (parsed.type() == typeid(dictionary_type)) {
        const dictionary_type &out = boost::any_cast<const dictionary_type&>(parsed);
        std::cout << "Parsed keys: " << out.size() << "\n";
        return 0;
    }
    std::cout << "Unexpected type" << std::endl;
    return 1;
}
