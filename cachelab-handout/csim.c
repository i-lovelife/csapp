#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int timestamps[40][6];
unsigned long long tag[40][6];
int s, S, E, b, B;

FILE *infile;
char infile_line[256];
int main(int argc, char **argv)
{
    int i, j;
    s = -1, E = -1, b = -1;
    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-s", 2) == 0 && i + 1 < argc) {
            sscanf(argv[i + 1], "%d", &s);
            i++;
            continue;
        }
        if (strncmp(argv[i], "-E", 2) == 0 && i + 1 < argc) {
            sscanf(argv[i + 1], "%d", &E);
            i++;
            continue;
        }
        if (strncmp(argv[i], "-b", 2) == 0 && i + 1 < argc) {
            sscanf(argv[i + 1], "%d", &b);
            i++;
            continue;
        }
        if (strncmp(argv[i], "-t", 2) == 0 && i + 1 < argc) {
            if (!(infile = fopen(argv[i + 1], "r"))) {
                printf("%s: Error: Couldn't open %s\n", argv[0], argv[i + 1]);
                exit(8);
	        }
            i++;
            continue;
        }
    }
    if (!infile || s < 0 || E < 0 || b < 0) {
        printf("usage: ./csim -s <num> -E <num> -b <num> -t <file>\n");
        exit(0);
    }

    S = 1<<s;
    B = 1<<b;
    for (i = 0; i < S; i++) {
        for (j = 0; j < E; j++) {
            timestamps[i][j] = -1;
        }
    }

    int hit_count=0, miss_count=0, eviction_count=0;

    unsigned long long request_address;
    int request_num;
    char ins_type;
    int line_no = 0;
    while (fgets(infile_line, sizeof(infile_line), infile)) {
        line_no ++;
        if (!strlen(infile_line)) {
            continue;
        }
        if (infile_line[0] == 'I') {
            continue;
        }
        if (infile_line[0] == ' ') {
            sscanf(infile_line, " %c%llX,%d\n", &ins_type, &request_address, &request_num);
            printf("%c %lld %d\n", ins_type, request_address, request_num);
            printf("hit=%d miss=%d eviction=%d\n", hit_count, miss_count, eviction_count);
            int s_index = (int) (request_address >> b & (S - 1));
            int last_s_index = (int) ((request_address + request_num - 1) >> b & (S - 1));
            printf("s_index= %d last_s_index=%d\n", s_index, last_s_index);
            unsigned long long tag_index = request_address >> (b + s);
            for (; s_index <= last_s_index; s_index++) {
                int find = -1;
                for (i = 0; i < E; i++) {
                    if (timestamps[s_index][i] >= 0 && tag_index == tag[s_index][i]) {
                        find = i;
                        break;
                    }
                }
                if (find >= 0) {
                    hit_count++;
                    timestamps[s_index][find] = line_no;
                }
                else {
                    miss_count++;
                    int evision = -1;
                    int need_evision = 1;
                    for (i = 0; i < E; i++) {
                        if (timestamps[s_index][i] < 0) {
                            timestamps[s_index][i] = line_no;
                            tag[s_index][i] = tag_index;
                            need_evision = 0;
                            break;
                        }
                        else {
                            if (evision < 0 || timestamps[s_index][i] < timestamps[s_index][evision]) {
                                evision = i;
                            }
                        }
                    }
                    if (need_evision) {
                        tag[s_index][evision] = tag_index;
                        timestamps[s_index][evision] = line_no;
                        eviction_count++;
                    }
                }
                if (ins_type == 'M') {
                    hit_count ++;
                }
            }
        }
    }
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
