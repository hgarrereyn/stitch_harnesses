#include <OpenXLSX/OpenXLSX.hpp>
#include <iostream>

int main() {
    try {
        OpenXLSX::XLDocument doc;
        doc.create("TestSpreadsheet.xlsx");
        auto wks = doc.workbook().worksheet("Sheet1");
        wks.cell("A1").value() = "Hello from OpenXLSX";
        wks.cell("B1").value() = 42;
        doc.save();
        doc.close();
        std::cout << "Created TestSpreadsheet.xlsx\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
