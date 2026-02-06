#include <cstdio>
#include <SimpleMath.h>

int main(){
    using namespace DirectX::SimpleMath;
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    Vector3 c = a + b;
    printf("%f %f %f\n", c.x, c.y, c.z);
    Matrix m = Matrix::CreateRotationZ(3.14159f * 0.5f);
    Vector3 d = Vector3::Transform(a, m);
    printf("%f %f %f\n", d.x, d.y, d.z);
    return 0;
}
