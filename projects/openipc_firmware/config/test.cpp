#include <iostream>
#include <cstdint>
#include <cstring>

// Include MAVLink umbrella first to define required macros, then helpers
#include <mavlink/common/mavlink.h>
#include <mavlink/mavlink_helpers.h>

int main() {
    // Access channel status and buffer via header-defined helpers
    mavlink_status_t* st = mavlink_get_channel_status(0);
    mavlink_message_t* buf = mavlink_get_channel_buffer(0);

    // Initialize some fields to avoid unused-variable warnings
    st->parse_state = MAVLINK_PARSE_STATE_IDLE;
    st->packet_idx = 0;
    st->current_rx_seq = 0;
    st->current_tx_seq = 0;

    std::memset(buf, 0, sizeof(*buf));
    buf->magic = MAVLINK_STX;
    buf->len = 0;

    std::cout << "MAVLink helper test OK: magic=" << (int)buf->magic << ", state=" << (int)st->parse_state << std::endl;
    return 0;
}
