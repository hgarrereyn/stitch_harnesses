#include <cstdio>
#include <cstring>
extern "C" {
#include <xlsxwriter.h>
}

int main() {
    // Create a simple workbook and worksheet and write some values.
    lxw_workbook *workbook = workbook_new("/tmp/test.xlsx");
    if (!workbook) {
        std::printf("Failed to create workbook\n");
        return 1;
    }

    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    if (!worksheet) {
        std::printf("Failed to add worksheet\n");
        workbook_close(workbook);
        return 1;
    }

    worksheet_write_string(worksheet, 0, 0, "Hello Excel", NULL);
    worksheet_write_number(worksheet, 1, 0, 123.456, NULL);

    int rc = workbook_close(workbook);
    std::printf("workbook_close returned %d\n", rc);
    return 0;
}
