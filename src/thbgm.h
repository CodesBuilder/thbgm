/**
 * @file thbgm.h
 * @author CodesBuilder (2602783536@qq.com)
 * @brief Format definitions for THBGM files.
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#ifndef _THBGM_THBGM_H__
#define _THBGM_THBGM_H__

#include <stdint.h>

typedef struct _thbgm_entry_t {
	uint32_t offBegin;
	uint32_t offEnd;
	uint32_t offLoopBegin;
	uint32_t offLoopEnd;
	uint8_t wavFileHdr[16];
	uint32_t reserved;
} thbgm_entry_t;

#endif
