#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

void printHelpInfo();
void readInput();
void readFile();
void initCache();
void accessCache();

unsigned s, E, b;
unsigned hit_count = 0, miss_count = 0, eviction_count = 0;
FILE *pFile;

char operation;
int address;
int size;

typedef struct {
	short Valid_bit;
	int Tag;
	int LRU_counter;
} cache_line;
cache_line **cache;

int main(int argc, char **argv) {
	readInput(argc, argv);
	initCache();
	readFile();
	free(cache);
	fclose(pFile);

	printSummary(hit_count, miss_count, eviction_count);

	return 0;
}

void readFile() {
	while (fscanf(pFile, " %c %x,%d", &operation, &address, &size) > 0) {
		switch (operation) {
		case 'L':
			accessCache();
			break;
		case 'M':
			accessCache();
		case 'S':
			accessCache();
			break;
		}
	}
}

void readInput(int argc, char **argv) {
	int opt;
	while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
		switch (opt) {
		case 's':
			s = atoi(optarg);
			break;
		case 'E':
			E = atoi(optarg);
			break;
		case 'b':
			b = atoi(optarg);
			break;
		case 't':
			pFile = fopen(optarg, "r");
			break;
		case 'h':
		default:
			printHelpInfo();
			break;
		}
	}
}

void initCache() {
	unsigned S = (1 << s);
	cache = (cache_line **)malloc(sizeof(cache_line*) << s);
	for (int i = 0; i < S; i++) {
		cache[i] = (cache_line *)malloc(sizeof(cache_line) * E);
	}

	for (int i = 0; i < S; i++) {
		for (int j = 0; j < E; j++) {
			cache[i][j].LRU_counter = -1;
			cache[i][j].Valid_bit = 0;
			cache[i][j].Tag = -1;
		}
	}
}

void accessCache() {
	int tag = address >> b >> s;
	int setIndex = (address >> b) ^ (tag << s);
	int evictionIndex = 0;
	int sign = 0;
	cache_line * set = cache[setIndex];


	for (int i = 0; i < E; i++) {
		if (set[i].Valid_bit == 1) {
			if (set[i].Tag == tag) {
				set[i].LRU_counter = 0;
				hit_count++;
				sign = 1;
				continue;
			}
			else {
				set[i].LRU_counter++;
				if (set[i].LRU_counter > set[evictionIndex].LRU_counter) {
					evictionIndex = i;
				}
				continue;
			}
		}
		else {
			if (sign) {
				return;
			}
			else {
				miss_count++;
				set[i].Tag = tag;
				set[i].LRU_counter = 0;
				set[i].Valid_bit = 1;
				return;
			}
		}
	}

	if (!sign) {
		eviction_count++;
		miss_count++;

		set[evictionIndex].Tag = tag;
		set[evictionIndex].LRU_counter = 0;
	}
}

void printHelpInfo() {
	printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("  -h         Print this help message.\n");
	printf("  -v         Optional verbose flag.\n");
	printf("  -s <num>   Number of set index bits.\n");
	printf("  -E <num>   Number of lines per set.\n");
	printf("  -b <num>   Number of block offset bits.\n");
	printf("  -t <file>  Trace file.\n\n");
	printf("Examples:\n");
	printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
	printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

