#include <stddef.h>

/*
 * Link-only Android OpenSL ES stub.
 * NICHT in die APK packen.
 */

void *SL_IID_VOLUME;
void *SL_IID_ENGINE;
void *SL_IID_ANDROIDSIMPLEBUFFERQUEUE;
void *SL_IID_RECORD;
void *SL_IID_PLAY;

int slCreateEngine(void *pEngine,
                   unsigned int numOptions,
                   const void *pEngineOptions,
                   unsigned int numInterfaces,
                   const void *pInterfaceIds,
                   const void *pInterfaceRequired)
{
    (void)pEngine;
    (void)numOptions;
    (void)pEngineOptions;
    (void)numInterfaces;
    (void)pInterfaceIds;
    (void)pInterfaceRequired;
    return -1;
}
