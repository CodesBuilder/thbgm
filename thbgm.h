#ifndef _THBGM_THBGM_H__
#define _THBGM_THBGM_H__

#include <stdint.h>

typedef struct _thbgm_entry_t {
    char fileName[16];
    uint32_t offBegin;
    uint32_t offEnd;
    uint32_t offLoopBegin;
    uint32_t offLoopEnd;
    uint8_t wavFileHdr[16];
    uint8_t reserved[4];
} thbgm_entry_t;

#endif
