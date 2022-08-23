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

	// Get file size
	long size = 0;
	{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if (size < 0) {
			fclose(fp);
			puts("Error getting file size");
			return -1;
		}
	}

	// Check if the file was aligned
	if (size % sizeof(thbgm_entry_t)) {
		size -= (size % sizeof(thbgm_entry_t));
		puts("Warning: The file was not aligned!");
	}

	// Read for each entries and print them with BGMForAll format
	for (long i = 0, j = 0; i < size; i += sizeof(thbgm_entry_t), j++) {
		thbgm_entry_t entry;
		if (!fread(&entry, sizeof(thbgm_entry_t), 1, fp)) {
			fclose(fp);
			puts("Error reading file");
			return -1;
		}

		printf(
			"BGM = %s, 0x%x, 0x%x, 0x%x, 0x%x\n",
			entry.fileName,
			entry.offBegin,
			entry.offLoopBegin,
			entry.offBegin + entry.offLoopBegin,
			entry.offLoopEnd - entry.offLoopBegin);
	}
	fclose(fp);
	return 0;
}
