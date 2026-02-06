#include <qpdf/QPDF.hh>
#include <qpdf/QPDFWriter.hh>
#include <qpdf/Pl_Buffer.hh>
#include <iostream>

int main() {
    try {
        QPDF qpdf;
        qpdf.emptyPDF();
        QPDFWriter w(qpdf);
        w.setOutputMemory();
        w.setCompressStreams(true);
        w.write();
        std::shared_ptr<Buffer> buf = w.getBufferSharedPointer();
        if (buf && buf->getSize() >= 5) {
            std::string header(reinterpret_cast<const char*>(buf->getBuffer()), 5);
            std::cout << header << "\n";
        } else {
            std::cout << "no-data\n";
        }
    } catch (std::exception const& e) {
        std::cout << "exception: " << e.what() << "\n";
    }
    return 0;
}
