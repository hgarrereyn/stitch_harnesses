#include <Python.h>
#include <stdio.h>
int main() {
    Py_Initialize();
    PyRun_SimpleString("import sys; sys.stdout.write('hello from embedded python\\n')");
    if (PyErr_Occurred()) {
        PyErr_Print();
    }
    Py_Finalize();
    printf("Done.\n");
    return 0;
}
