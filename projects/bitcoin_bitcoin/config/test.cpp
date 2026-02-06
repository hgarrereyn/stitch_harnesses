#include <cstdio>
#include <bitcoinkernel.h>

int main() {
    btck_logging_disable();

    btck_LoggingOptions opts{};
    opts.log_timestamps = 1;
    btck_logging_set_options(opts);
    btck_logging_set_level_category(btck_LogCategory_ALL, btck_LogLevel_INFO);

    btck_ChainParameters* params = btck_chain_parameters_create(btck_ChainType_REGTEST);
    if (!params) return 1;

    btck_ContextOptions* copts = btck_context_options_create();
    if (!copts) { btck_chain_parameters_destroy(params); return 1; }

    btck_context_options_set_chainparams(copts, params);

    btck_Context* ctx = btck_context_create(copts);
    if (!ctx) { btck_context_options_destroy(copts); btck_chain_parameters_destroy(params); return 1; }

    btck_context_destroy(ctx);
    btck_context_options_destroy(copts);
    btck_chain_parameters_destroy(params);

    std::printf("bitcoinkernel basic test OK\n");
    return 0;
}
