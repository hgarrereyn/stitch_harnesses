#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <aqi.h>
}

int main() {
    float zero[24];
    for (int i = 0; i < 24; ++i) zero[i] = 0.0f;

    float co[24];
    float no2[24];
    float o3[24];
    float so2[24];
    float pm10[24];
    float pm25[24];
    for (int i = 0; i < 24; ++i) {
        co[i] = 1000.0f;
        no2[i] = 50.0f;
        o3[i] = 120.0f;
        so2[i] = 20.0f;
        pm10[i] = 40.0f;
        pm25[i] = 20.0f;
    }

    int us_aqi = calc_united_states_aqi(co, zero, zero, no2, o3, zero, so2, pm10, pm25);
    const char* desc = united_states_aqi_desc(us_aqi);

    std::printf("US AQI: %d (%s)\n", us_aqi, desc);

    int max_val = aqi_scale_max(UNITED_STATES_AQI);
    const char* desc2 = aqi_desc(UNITED_STATES_AQI, us_aqi);
    std::printf("Max: %d, Desc via generic API: %s\n", max_val, desc2);

    int generic = calc_aqi(UNITED_STATES_AQI, co, zero, zero, no2, o3, zero, so2, pm10, pm25);
    std::printf("Generic calc AQI: %d\n", generic);

    return 0;
}
