#include <cstdio>
#include <cstdlib>
#include <string>
extern "C" {
#include <hpdf.h>
}

static void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
    (void)user_data;
    fprintf(stderr, "libharu error: %04X, detail: %d\n", (HPDF_UINT)error_no, (HPDF_INT)detail_no);
}

int main() {
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    if (!pdf) {
        fprintf(stderr, "Failed to create HPDF_Doc\n");
        return 1;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetWidth(page, 200);
    HPDF_Page_SetHeight(page, 200);

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, font, 16);
    HPDF_Page_TextOut(page, 20, 100, "Hello, libharu!");
    HPDF_Page_EndText(page);

    const char* out = "/tmp/libharu_test.pdf";
    if (HPDF_SaveToFile(pdf, out) != 0) {
        fprintf(stderr, "Failed to save PDF\n");
        HPDF_Free(pdf);
        return 1;
    }

    HPDF_Free(pdf);
    // Print path so test harness has some output
    printf("Created %s\n", out);
    return 0;
}
