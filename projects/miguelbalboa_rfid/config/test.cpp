#include <iostream>
#include <MFRC522.h>

int main() {
    MFRC522 rfid; // default SS and no reset
    byte ver = rfid.PCD_ReadRegister(MFRC522::VersionReg);
    std::cout << "MFRC522 VersionReg: " << static_cast<int>(ver) << std::endl;
    return 0;
}
