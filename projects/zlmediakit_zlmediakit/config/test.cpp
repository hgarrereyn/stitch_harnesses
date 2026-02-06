#include <stdio.h>
#include <string.h>
#include "mk_mediakit.h"

int main(){
    // Initialize with minimal settings: log to console only, no files
    mk_env_init2(1, /*thread_num*/
                 2, /*log_level*/
                 LOG_CONSOLE, /*log_mask*/
                 NULL, /*log_file_path*/
                 0, /*log_file_days*/
                 1, /*ini_is_path*/
                 NULL, /*ini - use default*/
                 1, /*ssl_is_path*/
                 NULL, /*ssl*/
                 NULL /*ssl_pwd*/);

    mk_set_option("general.enableVhost", "1");
    const char *val = mk_get_option("general.enableVhost");
    if(val){
        printf("mk_get_option general.enableVhost=%s\n", val);
    }

    mk_stop_all_server();
    return 0;
}
