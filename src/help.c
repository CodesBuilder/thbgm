/**
 * @file help.c
 * @author CodesBuilder (2602783536@qq.com)
 * @brief Implementations of 'help' operation
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#include <stdio.h>

#include "cmdop.h"

int cmdop_help(int argc, char** argv) {
	if (argc > 3) {
		puts("Bad usage");
	}

	puts("Usage: thbgm <operation> [arguments] ...\n");

	puts("Operations:");
	for (cmdop_t* i = cmdops; i->name != NULL; i++) {
		printf("\t%s\t%s\n", i->name, i->help);
	}

	puts(
		"\n"
		"Copyright (C) 2022 CodesBuilder & contributors\n"
		"This is free software, you can modify and redistribute it under the terms of license.");

	return 0;
}
