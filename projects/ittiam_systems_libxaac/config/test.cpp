#include <cstdio>
#include <cstring>

extern "C" {
#include "/fuzz/install/include/ixheaac_type_def.h"
#include "/fuzz/install/include/ixheaacd_memory_standards.h" // ia_lib_info_struct, ixheaacd_get_lib_id_strings
#include "/fuzz/install/include/ixheaace_api.h"             // encoder get_lib_id_strings
}

int main() {
    // Query decoder library ID strings
    ia_lib_info_struct dec_info{};
    dec_info.p_lib_name = nullptr;
    dec_info.p_version_num = nullptr;
    ixheaacd_get_lib_id_strings((pVOID)&dec_info);

    const char* dec_name = dec_info.p_lib_name ? (const char*)dec_info.p_lib_name : "(null)";
    const char* dec_ver  = dec_info.p_version_num ? (const char*)dec_info.p_version_num : "(null)";

    // Query encoder library ID strings
    ixheaace_output_config enc_out{}; // defined in ixheaace_api.h
    std::memset(&enc_out, 0, sizeof(enc_out));
    ixheaace_get_lib_id_strings((pVOID)&enc_out);
    const char* enc_name = enc_out.version.p_lib_name ? (const char*)enc_out.version.p_lib_name : "(null)";
    const char* enc_ver  = enc_out.version.p_version_num ? (const char*)enc_out.version.p_version_num : "(null)";

    std::printf("Decoder: %s, version: %s\n", dec_name, dec_ver);
    std::printf("Encoder: %s, version: %s\n", enc_name, enc_ver);

    // Simple sanity of types
    WORD32 sum = 0;
    for (int i = 0; i < 10; ++i) sum += i;
    std::printf("Sum=%d\n", sum);
    return 0;
}
