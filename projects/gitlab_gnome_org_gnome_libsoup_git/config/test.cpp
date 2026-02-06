#include <libsoup/soup.h>
#include <glib.h>
#include <stdio.h>

int main(){
    SoupSession *session = soup_session_new();
    if(!session){
        printf("Failed to create SoupSession\n");
        return 1;
    }

    SoupMessage *msg = soup_message_new("GET", "http://example.com/");
    if(!msg){
        printf("Failed to create SoupMessage\n");
        g_object_unref(session);
        return 1;
    }

    const char *method = soup_message_get_method(msg);
    GUri *uri = soup_message_get_uri(msg);
    char *uri_str = uri ? g_uri_to_string(uri) : NULL;
    printf("Method: %s\nURI: %s\n", method ? method : "(null)", uri_str ? uri_str : "(null)");
    g_free(uri_str);

    g_object_unref(msg);
    g_object_unref(session);
    return 0;
}
