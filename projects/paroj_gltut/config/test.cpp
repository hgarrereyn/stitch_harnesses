#include <glm/glm.hpp>
#include <framework/Interpolators.h>
#include <vector>
#include <iostream>
#include <cmath>

// helper free functions required by Interpolators
float distance(const glm::vec3 &lhs, const glm::vec3 &rhs) {
    glm::vec3 d = lhs - rhs;
    return std::sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
}

// For TimedLinearInterpolator helpers (not used here, but declared in header)
float GetValue(const std::pair<float,float> &data) { return data.second; }
float GetTime(const std::pair<float,float> &data) { return data.first; }

typedef std::pair<glm::vec4, float> LightVectorData; // match forward decl in header
glm::vec4 GetValue(const LightVectorData &data) { return data.first; }
float GetTime(const LightVectorData &data) { return data.second; }

int main() {
    // Use the header-only LinearInterpolator
    Framework::LinearInterpolator<float> lerp;
    std::vector<float> vals = {0.f, 10.f, 20.f};
    lerp.SetValues(vals, false);
    std::cout << "Interp(0.25)=" << lerp.Interpolate(0.25f) << "\n";
    return 0;
}
