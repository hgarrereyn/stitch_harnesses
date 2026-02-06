#include <iostream>
#include <vector>
#include <string>
#include <loot_loot/game_id.h>
#include <loot_loot/load_order_backup.h>

int main() {
    loot::GameId id = loot::GameId::tes5se;
    std::vector<std::string> order = {"Skyrim.esm", "Update.esm"};
    loot::LoadOrderBackup backup;
    backup.name = "test";
    backup.loadOrder = order;

    std::cout << "GameId numeric value: " << static_cast<int>(id) << "\n";
    std::cout << "Backup name: " << backup.name << ", entries: " << backup.loadOrder.size() << "\n";
    return 0;
}
