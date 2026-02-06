#include <blend2d/blend2d.h>

int main() {
  BLImage img(256, 256, BL_FORMAT_PRGB32);
  BLContext ctx(img);

  ctx.set_comp_op(BL_COMP_OP_SRC_COPY);
  ctx.fill_all();

  BLPath path;
  path.move_to(26, 31);
  path.cubic_to(80, 5, 80, 95, 130, 31);
  ctx.set_stroke_width(3.0);
  ctx.set_stroke_style(BLRgba32(0xFF00FF00u));
  ctx.stroke_path(path);

  ctx.end();
  return 0;
}
