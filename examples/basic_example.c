#include <ueum/ueum.h> /* include LibUnknownEchoUtilsModule */
#include <ei/ei.h> /* include LibErrorInterceptor */

int main() {
    char *data;

    ei_init(); /* initialize LibErrorInterceptor */

    /* use LibUnknownEchoUtilsModule */

    /* return the content of the file */
    data = ueum_read_file("test.txt");

    /* free data only if it's allocated */
    ueum_safe_free(data);

    /**
     * If the file test.txt doesn't exist or cannot be
     * opened, libueum will used libei to record an error
     * in the stacktrace of the current thread.
     * If so, we can print the stacktrace.
     */
    if (ei_stacktrace_is_filled()) {
        ei_stacktrace_print_all();
    }

    ei_uninit(); /* uninitialize LibErrorInterceptor */

    return 0;
}
