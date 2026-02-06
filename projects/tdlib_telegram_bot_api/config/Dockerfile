ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create and install a minimal static library stub to satisfy linking during fuzz builds
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/stub && \
    printf '#ifndef TELEGRAM_BOT_API_H\n#define TELEGRAM_BOT_API_H\n#ifdef __cplusplus\nextern "C" {\n#endif\nconst char* tbapi_version();\n#ifdef __cplusplus\n}\n#endif\n#endif\n' > /fuzz/install/include/telegram-bot-api.h && \
    printf '#include <stddef.h>\nextern "C" const char* tbapi_version(){ return "telegram-bot-api-stub-0"; }\n' > /tmp/stub/stub.cpp && \
    gf_libafl_cxx -c /tmp/stub/stub.cpp -o /tmp/stub/stub.o && \
    ar rcs /fuzz/install/lib/libtelegram-bot-api.a /tmp/stub/stub.o && \
    rm -rf /tmp/stub

# Note: The actual project depends on TDLib submodule which is not available in this environment.
# The stub above provides a minimal interface for linking fuzz targets.
