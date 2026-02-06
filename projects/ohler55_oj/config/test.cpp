#include <ruby.h>
#include <stdio.h>

static VALUE require_str(VALUE path) {
    return rb_require(StringValueCStr(path));
}

static void print_last_error() {
    VALUE err = rb_errinfo();
    if (!NIL_P(err)) {
        VALUE msg = rb_funcall(err, rb_intern("to_s"), 0);
        VALUE cls = rb_class_name(CLASS_OF(err));
        fprintf(stderr, "Ruby exception (%s): %s\n", StringValueCStr(cls), StringValueCStr(msg));
        rb_set_errinfo(Qnil);
    }
}

int main() {
    ruby_init();
    ruby_init_loadpath();

    // Add our installed Ruby library path
    VALUE load_path = rb_gv_get("$:"); // $LOAD_PATH
    rb_ary_unshift(load_path, rb_str_new_cstr("/fuzz/install/lib/ruby"));

    int state = 0;
    VALUE feature = rb_str_new_cstr("oj");
    rb_protect(require_str, feature, &state);
    if (state) {
        print_last_error();
        fprintf(stderr, "Failed to require oj.\n");
        return 1;
    }

    VALUE oj_mod = rb_const_get(rb_cObject, rb_intern("Oj"));

    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, rb_str_new_cstr("one"), INT2NUM(1));
    rb_hash_aset(hash, rb_str_new_cstr("two"), Qtrue);

    VALUE json = rb_funcall(oj_mod, rb_intern("dump"), 1, hash);
    Check_Type(json, T_STRING);

    printf("JSON: %s\n", StringValueCStr(json));

    ruby_cleanup(0);
    return 0;
}
