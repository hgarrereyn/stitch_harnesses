#include <iostream>
#include <DirectXMath.h>

int main() {
    using namespace DirectX;
    XMVECTOR a = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
    XMVECTOR b = XMVectorSet(4.0f, 5.0f, 6.0f, 0.0f);
    XMVECTOR c = XMVectorAdd(a, b);
    XMFLOAT3 out{};
    XMStoreFloat3(&out, c);
    std::cout << "sum: " << out.x << ", " << out.y << ", " << out.z << "\n";
    float len = XMVectorGetX(XMVector3Length(a));
    std::cout << "len(a): " << len << "\n";
    return 0;
}
