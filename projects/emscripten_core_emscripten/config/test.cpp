#include <cstdio>
#include <cstring>
#include <stb_image.h>

int main() {
    // Create a tiny buffer that is not a valid image.
    unsigned char buf[16];
    for (int i = 0; i < 16; ++i) buf[i] = (unsigned char)i;
    int x=0, y=0, comp=0;
    int ok = stbi_info_from_memory(buf, (int)sizeof(buf), &x, &y, &comp);
    std::printf("stbi_info_from_memory returned %d (x=%d y=%d comp=%d)\n", ok, x, y, comp);
    stbi_set_flip_vertically_on_load(0);
    return 0;
}
