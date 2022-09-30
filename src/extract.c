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
#include <malloc.h>
#include <memory.h>
#include <stdio.h>

#include "cmdop.h"
#include "thbgm.h"

int cmdop_extract(int argc, char** argv) {
	if (argc != 4) {
		puts("Bad usage");
		return -1;
	}

	const char* fmtPath = argv[2];
	const char* bgmPath = argv[3];

	FILE *fmtFp, *bgmFp;
	if (!(fmtFp = fopen(fmtPath, "rb"))) {
		printf("Error opening file '%s'\n", fmtPath);
		return -1;
	}
	if (!(bgmFp = fopen(bgmPath, "rb"))) {
		printf("Error opening file '%s'\n", bgmPath);
		return -1;
	}

	// Read for each entries and extract them
	while (1) {
		char filename[16];
		thbgm_entry_t entry;
		FILE* wavFp;
		uint32_t totalSize;

		if (!fread(&filename, sizeof(filename), 1, fmtFp)) {
			printf("Error reading name from file '%s'\n", fmtPath);
			goto fail;
		}
		if (!filename[0])
			break;
		if (!fread(&entry, sizeof(entry), 1, fmtFp)) {
			printf("Error reading entry from file '%s'\n", fmtPath);
			goto fail;
		}

		totalSize = entry.offEnd;

		if (!(wavFp = fopen(filename, "wb"))) {
			printf("Error opening file '%s' for writing\n", filename);
			goto fail;
		}

		struct {
			uint8_t riffId[4];
			uint32_t totalSize;
			uint8_t resId[4];

			uint8_t fmtId[4];
			uint32_t chunkSize;
			uint8_t metadata[16];

			uint8_t dataId[4];
			uint32_t dataSize;
		} wavHdr = {
			.riffId = { 'R', 'I', 'F', 'F' },
			.totalSize = totalSize + sizeof(wavHdr) - 8,
			.resId = { 'W', 'A', 'V', 'E' },
			.fmtId = { 'f', 'm', 't', 0x20 },
			.chunkSize = 16,
			.metadata = { '0' },
			.dataId = { 'd', 'a', 't', 'a' },
			.dataSize = totalSize
		};
		memcpy(wavHdr.metadata, entry.wavFileHdr, sizeof(wavHdr.metadata));

		if (!fwrite(&wavHdr, sizeof(wavHdr), 1, wavFp)) {
			fclose(wavFp);
			printf("Error writing file '%s'\n", filename);
			goto fail;
		}

		char* buffer = malloc(totalSize);
		if (!buffer) {
			fclose(wavFp);
			printf("Out of memory, %u bytes requested\n", totalSize);
			goto fail;
		}

		fseek(bgmFp, entry.offBegin, SEEK_SET);
		if (!fread(buffer, totalSize, 1, bgmFp)) {
			free(buffer);
			fclose(wavFp);
			printf("Error reading audio data from file '%s', total size = %u bytes\n", bgmPath, totalSize);
			goto fail;
		}
		if (!fwrite(buffer, totalSize, 1, wavFp)) {
			free(buffer);
			fclose(wavFp);
			printf("Error writing file '%s'\n", filename);
			goto fail;
		}

		free(buffer);
		fclose(wavFp);
	}

	fclose(bgmFp);
	fclose(fmtFp);
	return 0;

fail:
	fclose(bgmFp);
	fclose(fmtFp);
	return -1;
}
