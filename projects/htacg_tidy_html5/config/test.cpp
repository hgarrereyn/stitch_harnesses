#include <tidy.h>
#include <tidybuffio.h>
#include <cstring>
#include <iostream>

int main() {
    const char* html = "<html><title>t</title><body><p>hello"; // intentionally not closed properly

    TidyDoc tdoc = tidyCreate();
    if (!tdoc) {
        std::cerr << "tidyCreate failed\n";
        return 1;
    }

    tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
    tidyOptSetInt(tdoc, TidyWrapLen, 0);

    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    tidyBufInit(&output);
    tidyBufInit(&errbuf);

    int rc = tidySetErrorBuffer(tdoc, &errbuf);
    if (rc >= 0) rc = tidyParseString(tdoc, html);
    if (rc >= 0) rc = tidyCleanAndRepair(tdoc);
    if (rc >= 0) rc = tidyRunDiagnostics(tdoc);
    if (rc >= 0) rc = tidySaveBuffer(tdoc, &output);

    std::cout << "Output:\n";
    if (output.bp && output.size) {
        std::cout.write(reinterpret_cast<char*>(output.bp), output.size);
        std::cout << "\n";
    }
    std::cout << "Diagnostics:\n";
    if (errbuf.bp && errbuf.size) {
        std::cout.write(reinterpret_cast<char*>(errbuf.bp), errbuf.size);
        std::cout << "\n";
    }

    tidyBufFree(&output);
    tidyBufFree(&errbuf);
    tidyRelease(tdoc);
    return 0;
}
