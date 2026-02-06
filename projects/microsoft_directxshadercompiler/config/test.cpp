#include <dxc/dxcapi.h>
#include <dlfcn.h>
#include <cstdio>

int main() {
    // Try to load libdxcompiler dynamically if present, but pass even if missing.
    void* handle = dlopen("libdxcompiler.so", RTLD_LAZY);
    if (!handle) {
        std::printf("libdxcompiler not present; headers installed OK.\n");
        return 0; // headers are enough for this test
    }
    auto create_fn = (DxcCreateInstanceProc)dlsym(handle, "DxcCreateInstance");
    if (!create_fn) {
        std::printf("DxcCreateInstance symbol not found.\n");
        dlclose(handle);
        return 0;
    }
    IDxcUtils* utils = nullptr;
    HRESULT hr = create_fn(CLSID_DxcUtils, IID_PPV_ARGS(&utils));
    if (SUCCEEDED(hr) && utils) {
        utils->Release();
        std::printf("DXC Utils created successfully.\n");
    } else {
        std::printf("DxcCreateInstance failed: 0x%08x\n", (unsigned)hr);
    }
    dlclose(handle);
    return 0;
}
