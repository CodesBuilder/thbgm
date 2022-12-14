/**
 * @file main.c
 * @author CodesBuilder (2602783536@qq.com)
 * @brief THBGM main program.
 * @version 0.1
 * @date 2022-08-22
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#include <stdio.h>
#include <string.h>

#include "cmdop.h"
#include "thbgm.h"

cmdop_t cmdops[] = {
	{ .name = "list", .proc = cmdop_list, .help = "List music entries from THFMT files" },
	{ .name = "help", .proc = cmdop_help, .help = "Display the help message" },
	{ .name = "extract", .proc = cmdop_extract, .help = "Extract an THBGM file" },
	{ NULL }
};

//
// Main implementation
//
int main(int argc, char** argv) {
	if (argc < 2) {
		puts("Too few arguments");
		return -1;
	}

	const char* op = argv[1];

	//
	// Match for each command entries
	//
	{
		for (cmdop_t* i = cmdops; i->name != NULL; i++) {
			if (!strcmp(op, i->name))
				return i->proc(argc, argv);
		}
	}

	printf("Unknown operation '%s'\n", op);
	return -1;
}
