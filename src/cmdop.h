/**
 * @file cmdop.h
 * @author CodesBuilder (2602783536@qq.com)
 * @brief Definitions for operations and operation registries
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#ifndef _THBGM_CMDOP_H
#define _THBGM_CMDOP_H

//
// Command declarations
//
int cmdop_list(int argc, char** argv);
int cmdop_help(int argc, char** argv);
int cmdop_hand(int argc, char** argv);

//
// Command operation entries
//
typedef struct _cmdop_t {
    const char* name;
    int (*proc)(int argc, char** argv);
    const char* help;
}cmdop_t;

extern cmdop_t cmdops[];

#endif
