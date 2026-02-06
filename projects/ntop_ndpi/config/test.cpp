#include <stdio.h>
#include <string.h>
#include <ndpi_api.h>

int main() {
  struct ndpi_global_context *g = ndpi_global_init();
  if(!g) { printf("global init failed\n"); return 1; }
  struct ndpi_detection_module_struct *mod = ndpi_init_detection_module(g);
  if(!mod) { printf("module init failed\n"); ndpi_global_deinit(g); return 1; }
  if(ndpi_finalize_initialization(mod) != 0) {
    printf("finalize failed\n");
    ndpi_exit_detection_module(mod);
    ndpi_global_deinit(g);
    return 1;
  }
  struct ndpi_flow_struct *flow = (struct ndpi_flow_struct*) ndpi_malloc(sizeof(struct ndpi_flow_struct));
  if(!flow) { printf("flow alloc failed\n"); ndpi_exit_detection_module(mod); ndpi_global_deinit(g); return 1; }
  memset(flow, 0, sizeof(*flow));
  ndpi_protocol p = ndpi_detection_giveup(mod, flow);
  (void)p;
  ndpi_free_flow(flow);
  ndpi_exit_detection_module(mod);
  ndpi_global_deinit(g);
  printf("nDPI basic init/exit OK\n");
  return 0;
}
