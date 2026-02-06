#include <dpp/dpp.h>
#include <iostream>

int main() {
    // Basic construction of a few core types without connecting to Discord
    dpp::snowflake id = 123456789012345678ULL;
    dpp::user u;
    u.id = id;
    u.username = "test_user";

    dpp::message m("Hello, DPP!");
    m.set_guild_id(0);
    m.set_channel_id(0);

    dpp::embed e;
    e.set_title("Test").set_description("Embed body");
    m.add_embed(e);

    // Construct a cluster with a dummy token (we will not start it)
    dpp::cluster bot("dummy_token");

    std::cout << "Constructed objects: user=" << u.username << ", embeds=" << m.embeds.size() << "\n";
    return 0;
}
