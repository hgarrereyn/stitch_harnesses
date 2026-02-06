#include <cstdio>
extern "C" {
#include <pf_math.h>
}

int main(){
    vec3_t a; a.x = 1.0f; a.y = 2.0f; a.z = 3.0f;
    vec3_t b; b.x = -4.0f; b.y = 5.0f; b.z = -6.0f;
    GLfloat dot = PFM_Vec3_Dot(&a, &b);
    vec3_t c; PFM_Vec3_Cross(&a, &b, &c);
    printf("dot=%.2f, cross=(%.2f,%.2f,%.2f)\n", dot, c.x, c.y, c.z);
    mat4x4_t m; PFM_Mat4x4_Identity(&m);
    printf("m00=%.1f m33=%.1f\n", m.cols[0][0], m.cols[3][3]);
    return 0;
}
