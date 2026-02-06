#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
extern "C" {
#include "/fuzz/install/include/opensips/sha256.h"
#include "/fuzz/install/include/opensips/md5.h"
}

static std::string hex(const unsigned char *buf, size_t len){
    static const char* kHex = "0123456789abcdef";
    std::string out; out.reserve(len*2);
    for(size_t i=0;i<len;i++){ unsigned char c=buf[i]; out.push_back(kHex[c>>4]); out.push_back(kHex[c&0xF]); }
    return out;
}

int main(){
    const char* msg = "hello opensips";

    // SHA-256
    unsigned char sha[32];
    sha256((const unsigned char*)msg, strlen(msg), sha, /*is224=*/0);
    std::string sha_hex = hex(sha, 32);

    // MD5
    MD5_CTX ctx; char md5_out[16];
    MD5Init(&ctx); MD5Update(&ctx, msg, (unsigned int)strlen(msg)); MD5Final(md5_out, &ctx);
    std::string md5_hex = hex(reinterpret_cast<unsigned char*>(md5_out), 16);

    printf("sha256=%s\nmd5=%s\n", sha_hex.c_str(), md5_hex.c_str());
    return 0;
}
