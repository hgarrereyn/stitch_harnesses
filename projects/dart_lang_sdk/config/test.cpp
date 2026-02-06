#include <stdio.h>
#include <stdint.h>
#include "dart_api_dl.h"

extern "C" {
void Dart_UpdateExternalSize_Deprecated(Dart_WeakPersistentHandle object, intptr_t external_size);
void Dart_UpdateFinalizableExternalSize_Deprecated(Dart_FinalizableHandle object, Dart_Handle strong_ref_to_object, intptr_t external_allocation_size);
}

int main() {
    // These deprecated functions are provided by dart_api_dl.c and are safe to call
    // without initializing the Dart VM. They just print a message.
    Dart_UpdateExternalSize_Deprecated(nullptr, 0);
    Dart_UpdateFinalizableExternalSize_Deprecated(nullptr, nullptr, 0);

    // Ensure the function pointer variables exist; they should be NULL before initialization.
    if (Dart_IsError_DL == nullptr) {
        printf("Dart_IsError_DL is NULL as expected before initialization.\n");
    }
    printf("Test completed.\n");
    return 0;
}
