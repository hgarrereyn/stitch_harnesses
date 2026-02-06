#include <iostream>
#include <vestige/aeffectx.h>

intptr_t VST_CALL_CONV dummyAudioMaster(AEffect*, int, int, intptr_t, void*, float) {
    return 0;
}

int main() {
    std::cout << "kEffectMagic=" << kEffectMagic << "\n";
    std::cout << "audioMasterVersion=" << audioMasterVersion << "\n";

    AEffect eff{};
    eff.magic = kEffectMagic;
    eff.dispatcher = nullptr;
    eff.process = nullptr;
    eff.setParameter = nullptr;
    eff.getParameter = nullptr;
    eff.numPrograms = 1;
    eff.numParams = 0;
    eff.numInputs = 2;
    eff.numOutputs = 2;
    eff.flags = effFlagsCanReplacing;
    eff.ptr1 = nullptr;
    eff.ptr2 = nullptr;
    eff.initialDelay = 0;
    eff.empty3a = 0;
    eff.empty3b = 0;
    eff.unkown_float = 1.0f;
    eff.ptr3 = nullptr;
    eff.user = nullptr;
    eff.uniqueID = CCONST('T','E','S','T');
    eff.version = 1;
    eff.processReplacing = nullptr;
    eff.processDoubleReplacing = nullptr;

    if (eff.magic != kEffectMagic) return 1;
    return 0;
}
