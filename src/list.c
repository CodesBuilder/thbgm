/**
 * @file list.c
 * @author CodesBuilder (2602783536@qq.com)
 * @brief Implementations of 'list' operation
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 CodesBuilder and contributors
 *
 */
#include <stdio.h>

#include "cmdop.h"
#include "thbgm.h"

int cmdop_list(int argc, char** argv) {
	if (argc != 3) {
		puts("Bad usage");
		return -1;
	}

	FILE* fp;
	if (!(fp = fopen(argv[2], "rb"))) {
		printf("Error opening file '%s'\n", argv[2]);
		return -1;
	}

	// Read for each entries and print them with BGMForAll format
	while(1) {
		char filename[16];
		thbgm_entry_t entry;

		if (!fread(&filename, sizeof(filename), 1, fp)) {
			fclose(fp);
			puts("Error reading file");
			return -1;
		}

		if(!filename[0])
			break;

		if (!fread(&entry, sizeof(entry), 1, fp)) {
			fclose(fp);
			puts("Error reading file");
			return -1;
		}

		printf(
			"BGM = %s, 0x%x, 0x%x, 0x%x, 0x%x\n",
			filename,
			entry.offBegin,
			entry.offLoopBegin,
			entry.offBegin + entry.offLoopBegin,
			entry.offLoopEnd - entry.offLoopBegin);
	}
	fclose(fp);
	return 0;
}
