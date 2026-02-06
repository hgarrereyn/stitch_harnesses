#include <cstdio>
#include <cwchar>
#include <wchar.h>
#include "xcode_utf_fixed.h"

int main() {
    const wchar_t* ws = L"Hello \u013D world"; // include a wide char
    size_t n = wcslen_fixed(ws);
    int cmp = wcsncmp_fixed(L"abc\u013D", L"abd\u013D", 3);
    const wchar_t* pos = wcsstr_fixed(L"foo\u30afbar", L"\u30af");
    printf("wcslen_fixed=%zu, wcsncmp_fixed=%d, wcsstr_fixed_ofs=%ld\n", n, cmp, pos ? (long)(pos - (const wchar_t*)L"foo\u30afbar") : -1L);
    return 0;
}
