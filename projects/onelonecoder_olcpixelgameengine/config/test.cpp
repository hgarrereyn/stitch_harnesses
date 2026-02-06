// Build a minimal headless test that exercises some API without opening a window
#define OLC_PGE_HEADLESS
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Demo : public olc::PixelGameEngine {
public:
    Demo() { sAppName = "HeadlessDemo"; }
    bool OnUserCreate() override {
        // Create a simple sprite and draw a pixel
        olc::Sprite spr(4, 4);
        spr.SetPixel(1, 1, olc::RED);
        // Create a decal to touch that API
        olc::Decal d(&spr);
        // Draw to default layer
        Draw(1, 1, olc::WHITE);
        return true;
    }
    bool OnUserUpdate(float) override {
        // Draw a line each frame for a couple of frames then exit
        static int frames = 0;
        DrawLine(0, 0, 3, 3, olc::GREEN);
        return (++frames < 2);
    }
};

int main(){
    Demo demo;
    // Construct a tiny offscreen buffer; in headless this does not create a window
    if (demo.Construct(4, 4, 1, 1, false, false)) {
        demo.Start();
    }
    // Query some API to ensure linkage
    auto sz = demo.GetScreenSize();
    if (sz.x != 4 || sz.y != 4) return 1;
    return 0;
}
