#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cgif.h"

int main(){
  const uint16_t W = 16, H = 16;
  uint8_t palette[] = {
    0x00,0x00,0x00, // black
    0xFF,0x00,0x00, // red
    0x00,0xFF,0x00, // green
    0x00,0x00,0xFF  // blue
  };
  CGIF_Config cfg; memset(&cfg, 0, sizeof(cfg));
  cfg.width = W; cfg.height = H;
  cfg.pGlobalPalette = palette; cfg.numGlobalPaletteEntries = 4;
  cfg.path = "test_out.gif";
  CGIF* g = cgif_newgif(&cfg);
  if(!g){ fprintf(stderr, "cgif_newgif failed\n"); return 1; }
  uint8_t *img = (uint8_t*)malloc(W*H);
  for(unsigned y=0;y<H;y++){
    for(unsigned x=0;x<W;x++){
      img[y*W+x] = (uint8_t)((x/4 + y/4) % 4);
    }
  }
  CGIF_FrameConfig fcfg; memset(&fcfg, 0, sizeof(fcfg));
  fcfg.pImageData = img; fcfg.delay = 0;
  if(cgif_addframe(g, &fcfg) != 0){ fprintf(stderr, "cgif_addframe failed\n"); return 1; }
  free(img);
  if(cgif_close(g) != 0){ fprintf(stderr, "cgif_close failed\n"); return 1; }
  return 0;
}
