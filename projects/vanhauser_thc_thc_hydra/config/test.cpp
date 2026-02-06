#include <iostream>
#include <cstring>
extern "C" {
    void thcf_make_to_lower(char* s);
    void thcf_base64(unsigned char* buf, unsigned int buflen, unsigned int bufsize);
    int thcf_memsearch(char* h,int hl,char* n,int nl);
}

int main() {
    char buf[] = "HeLLo, WorLD!";
    thcf_make_to_lower(buf);

    unsigned char data[] = "abc";
    unsigned char outbuf[64];
    memset(outbuf, 0, sizeof(outbuf));
    memcpy(outbuf, data, 3);
    thcf_base64(outbuf, 3, sizeof(outbuf));

    int pos = thcf_memsearch((char*)"hello world", 11, (char*)"world", 5);

    std::cout << "lower: " << buf << " base64: " << outbuf << " pos: " << pos << std::endl;
    return 0;
}
