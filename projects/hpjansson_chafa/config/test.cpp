#include <chafa/chafa.h>
#include <stdio.h>
#include <string.h>

int main(){
    // Create a simple 2x2 RGB image (red, green, blue, white)
    unsigned char pixels[2*2*3];
    // row 0
    pixels[0]=255; pixels[1]=0;   pixels[2]=0;   // red
    pixels[3]=0;   pixels[4]=255; pixels[5]=0;   // green
    // row 1
    pixels[6]=0;   pixels[7]=0;   pixels[8]=255; // blue
    pixels[9]=255; pixels[10]=255; pixels[11]=255; // white

    ChafaCanvasConfig *conf = chafa_canvas_config_new();
    chafa_canvas_config_set_geometry(conf, 2, 2);

    ChafaCanvas *canvas = chafa_canvas_new(conf);

    chafa_canvas_draw_all_pixels(canvas, CHAFA_PIXEL_RGB8, pixels, 2, 2, 2*3);

    ChafaTermInfo *ti = chafa_term_info_new();
    GString *out = chafa_canvas_print(canvas, ti);

    // Print the generated string (may include escape codes)
    if(out){
        fwrite(out->str, 1, out->len, stdout);
        fputc('\n', stdout);
        g_string_free(out, TRUE);
    }

    chafa_term_info_unref(ti);
    chafa_canvas_unref(canvas);
    chafa_canvas_config_unref(conf);

    return 0;
}
