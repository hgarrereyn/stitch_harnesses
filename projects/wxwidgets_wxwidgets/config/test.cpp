#include <wx/string.h>
#include <wx/filename.h>
#include <wx/datetime.h>
#include <iostream>

int main() {
    wxString s = wxString::FromUTF8("Hello, wxWidgets base! ");
    s += wxString::Format("Number: %d", 42);

    wxFileName fn(wxString::FromUTF8("/tmp/test/path/file.txt"));
    wxString dirname = fn.GetPath();
    wxString basename = fn.GetName();

    wxDateTime now = wxDateTime::Now();
    wxString nowStr = now.FormatISOCombined(' ');

    std::cout << s.ToStdString() << "\n";
    std::cout << "Dir: " << dirname.ToStdString() << ", Base: " << basename.ToStdString() << "\n";
    std::cout << "Now: " << nowStr.ToStdString() << "\n";
    return 0;
}
