#include <iostream>
#include <libtorrent/version.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/settings_pack.hpp>
#include <libtorrent/session_status.hpp>

int main() {
    std::cout << "libtorrent version: " << LIBTORRENT_VERSION << "\n";

    libtorrent::settings_pack sp;
    sp.set_int(libtorrent::settings_pack::alert_mask, libtorrent::alert::error_notification);
    sp.set_bool(libtorrent::settings_pack::enable_dht, false);
    sp.set_bool(libtorrent::settings_pack::enable_lsd, false);
    sp.set_bool(libtorrent::settings_pack::enable_upnp, false);
    sp.set_bool(libtorrent::settings_pack::enable_natpmp, false);
    sp.set_str(libtorrent::settings_pack::listen_interfaces, "0.0.0.0:0,[::]:0");

    libtorrent::session ses(sp);
    libtorrent::session_status st = ses.status();
    std::cout << "Has incoming (recently): " << (st.has_incoming_connections ? 1 : 0) << "\n";

    return 0;
}
