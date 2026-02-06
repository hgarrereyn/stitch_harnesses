#include <cstdio>
#include <curl/curl.h>

int main() {
    const char *ver = curl_version();
    if (ver) {
        std::printf("libcurl version: %s\n", ver);
    }
    CURL *h = curl_easy_init();
    if (h) {
        curl_easy_setopt(h, CURLOPT_URL, "http://example.com/");
        curl_easy_cleanup(h);
    }
    return 0;
}
