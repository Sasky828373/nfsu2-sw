#if defined(__ANDROID__)
#include <android/log.h>
#include <pthread.h>
#include <stdlib.h>

extern int nfsu2_android_game_main(void);

static pthread_t g_game_thread;
static int g_started;

static void *android_game_thread(void *unused)
{
    (void)unused;
    __android_log_print(ANDROID_LOG_INFO, "NFSU2Recomp",
                        "starting native ARM64 recomp thread");
    nfsu2_android_game_main();
    return NULL;
}

/* Bootstrap entry point.  The Java/NativeActivity side calls this once after
 * storage is ready.  The 16 MiB stack matches the Switch host because lifted
 * functions can be very large. */
__attribute__((visibility("default")))
int nfsu2_android_start(void)
{
    pthread_attr_t attr;
    if (g_started)
        return 0;

    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 16u * 1024u * 1024u);
    if (pthread_create(&g_game_thread, &attr, android_game_thread, NULL) != 0) {
        pthread_attr_destroy(&attr);
        __android_log_print(ANDROID_LOG_ERROR, "NFSU2Recomp",
                            "failed to create game thread");
        return -1;
    }
    pthread_attr_destroy(&attr);
    pthread_detach(g_game_thread);
    g_started = 1;
    return 0;
}
#endif
