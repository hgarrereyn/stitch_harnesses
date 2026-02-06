#include <ArduinoJson.h>
#include <iostream>

int main() {
    JsonDocument doc;
    doc["sensor"] = "gps";
    doc["time"] = 1351824120;
    doc["data"][0] = 48.756080;
    doc["data"][1] = 2.302038;

    std::string out;
    serializeJson(doc, out);

    JsonDocument doc2;
    DeserializationError err = deserializeJson(doc2, out);
    if (err) {
        std::cerr << "Deserialization failed: " << err.c_str() << std::endl;
        return 1;
    }

    const char* sensor = doc2["sensor"].as<const char*>();
    long time = doc2["time"].as<long>();
    double lat = doc2["data"][0].as<double>();
    double lon = doc2["data"][1].as<double>();

    std::cout << sensor << "," << time << "," << lat << "," << lon << std::endl;
    return 0;
}
