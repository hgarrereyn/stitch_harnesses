#include <iostream>
#include <string>
#include "app/sprite_sheet_type.h"

int main() {
  app::SpriteSheetType t = app::SpriteSheetType::Rows;
  std::string name;
  switch (t) {
    case app::SpriteSheetType::None: name = "None"; break;
    case app::SpriteSheetType::Horizontal: name = "Horizontal"; break;
    case app::SpriteSheetType::Vertical: name = "Vertical"; break;
    case app::SpriteSheetType::Rows: name = "Rows"; break;
    case app::SpriteSheetType::Columns: name = "Columns"; break;
    case app::SpriteSheetType::Packed: name = "Packed"; break;
  }
  std::cout << "SpriteSheetType: " << name << "\n";
  return 0;
}
