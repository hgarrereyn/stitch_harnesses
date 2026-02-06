#include <Poco/Timestamp.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/MD5Engine.h>
#include <Poco/DigestEngine.h>
#include <iostream>
#include <iomanip>

int main() {
    // Use a few Foundation APIs
    Poco::Timestamp ts;
    auto epochTime = ts.epochTime();

    Poco::UUID uuid = Poco::UUIDGenerator::defaultGenerator().create();

    Poco::MD5Engine md5;
    std::string data = "hello-poco";
    md5.update(data);
    const std::string digest = Poco::DigestEngine::digestToHex(md5.digest());

    std::cout << "Epoch: " << epochTime << "\nUUID: " << uuid.toString() << "\nMD5: " << digest << std::endl;
    return 0;
}
