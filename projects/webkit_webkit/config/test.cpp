#include <stdio.h>
#include <xdgmime/xdgmime.h>

int main(void) {
    const char* file1 = "example.txt";
    const char* file2 = "image.png";
    const char* mime1 = xdg_mime_get_mime_type_from_file_name(file1);
    const char* mime2 = xdg_mime_get_mime_type_from_file_name(file2);
    printf("%s -> %s\n", file1, mime1 ? mime1 : "(null)");
    printf("%s -> %s\n", file2, mime2 ? mime2 : "(null)");
    return 0;
}
