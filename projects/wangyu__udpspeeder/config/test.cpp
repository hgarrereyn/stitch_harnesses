#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>

#include <fec.h>
#include <rs.h>

int main() {
    // Simple test for RS encode/decode
    int k = 3, n = 5; // 3 data + 2 parity
    int sz = 32; // bytes per shard

    void* code = fec_new(k, n);
    if (!code) {
        std::cerr << "fec_new failed" << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> bufs(n, std::vector<char>(sz));
    std::vector<char*> data(n, nullptr);

    // Fill original data
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < sz; ++j) bufs[i][j] = (char)(i * 10 + j);
        data[i] = bufs[i].data();
    }

    // rs_encode writes parity into data[k..n-1]
    for (int i = k; i < n; ++i) data[i] = bufs[i].data();
    rs_encode(code, data.data(), sz);

    // Simulate loss of one original shard
    data[1] = nullptr; // lost shard 1

    int ret = rs_decode(code, data.data(), sz);
    if (ret != 0) {
        std::cerr << "rs_decode failed" << std::endl;
        fec_free(code);
        return 1;
    }

    // Verify reconstructed shard 0..k-1 are correct
    bool ok = true;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < sz; ++j) {
            char expected = (char)(i * 10 + j);
            if (data[i][j] != expected) { ok = false; break; }
        }
        if (!ok) break;
    }

    fec_free(code);
    std::cout << (ok ? "OK" : "FAIL") << std::endl;
    return ok ? 0 : 1;
}
