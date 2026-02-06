#include <cstdio>
#include <cstring>
extern "C" {
#include "iv_datatypedef.h"
#include "iv.h"
#include "ivd.h"
#include "impeg2d.h"
#include "impeg2d_api.h"
}

int main() {
    // Prepare structs for version query (does not require a valid handle)
    impeg2d_ctl_getversioninfo_ip_t ip{};
    impeg2d_ctl_getversioninfo_op_t op{};

    char buf[256] = {0};

    ip.s_ivd_ctl_getversioninfo_ip_t.u4_size = sizeof(ip.s_ivd_ctl_getversioninfo_ip_t);
    ip.s_ivd_ctl_getversioninfo_ip_t.e_cmd = IVD_CMD_VIDEO_CTL;
    ip.s_ivd_ctl_getversioninfo_ip_t.e_sub_cmd = IVD_CMD_CTL_GETVERSION;
    ip.s_ivd_ctl_getversioninfo_ip_t.pv_version_buffer = buf;
    ip.s_ivd_ctl_getversioninfo_ip_t.u4_version_buffer_size = sizeof(buf);

    op.s_ivd_ctl_getversioninfo_op_t.u4_size = sizeof(op.s_ivd_ctl_getversioninfo_op_t);

    IV_API_CALL_STATUS_T st = impeg2d_api_get_version(nullptr, &ip, &op);
    std::printf("status=%d version=%.40s\n", (int)st, buf);
    return 0;
}
