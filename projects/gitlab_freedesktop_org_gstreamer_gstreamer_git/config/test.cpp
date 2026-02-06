#include <gst/gst.h>
#include <stdio.h>
int main(){
  int argc = 0; char **argv = NULL;
  gst_init(&argc, &argv);
  const gchar *v = gst_version_string();
  if(v) printf("GStreamer: %s\n", v);
  GstElement *pipeline = gst_pipeline_new("p");
  if (pipeline) {
    gst_object_unref(pipeline);
  }
  gst_deinit();
  return 0;
}
