#include <xdiff.h>
#include <string>
#include <iostream>
#include <cstring>

struct DiffSink {
  std::string out;
};

static int out_hunk_cb(void* priv, long old_begin, long old_nr, long new_begin, long new_nr, const char* func, long funclen) {
  (void)priv; (void)old_begin; (void)old_nr; (void)new_begin; (void)new_nr; (void)func; (void)funclen;
  return 0; // ignore hunk headers
}

static int out_line_cb(void* priv, mmbuffer_t* mb, int nbuf) {
  DiffSink* sink = static_cast<DiffSink*>(priv);
  for (int i = 0; i < nbuf; ++i) {
    sink->out.append(mb[i].ptr, (size_t)mb[i].size);
  }
  return 0;
}

int main() {
  const char* a = "line1\nline2\nlineX\nline4\n";
  const char* b = "line1\nline2\nline3\nline4\n";

  mmfile_t mf1; mf1.ptr = const_cast<char*>(a); mf1.size = (long)std::strlen(a);
  mmfile_t mf2; mf2.ptr = const_cast<char*>(b); mf2.size = (long)std::strlen(b);

  xpparam_t xpp = {};
  xdemitconf_t xecfg = {};
  xecfg.ctxlen = 3; // show context

  DiffSink sink;
  xdemitcb_t ecb = {};
  ecb.priv = &sink;
  ecb.out_hunk = &out_hunk_cb;
  ecb.out_line = &out_line_cb;

  int rc = xdl_diff(&mf1, &mf2, &xpp, &xecfg, &ecb);
  std::cout << "xdl_diff rc=" << rc << "\n";
  std::cout << sink.out << "\n";
  return 0;
}
