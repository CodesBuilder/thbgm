#ifndef _THBGM_CMDOP_H
#define _THBGM_CMDOP_H

//
// Command declarations
//
int cmdop_list(int argc, char** argv);

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
