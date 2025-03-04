#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"

void parse_file(char *filename, int m, char header_list[][m], int n, double data_array[][n]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Can't open file.\b");
        return;
    }

    char buf[10000]; // 8500 character buf | 306 counters
    int i = 0; // header_list index value

    // get first line of the csv file, parse using strtok and store contents in header_list
    fgets(buf, 10000, fp);
    char *field = strtok(buf, ",");
    while(field) {
        strcpy(header_list[i], field);
        field = strtok(NULL, ",");
        i++;
    }

    /* parse the remaining lines from the file and store the csv data in an n * m matrix */ 
    int j, k = 0; // index variables for the 2-D array 
    while(fgets(buf, 10000, fp) != NULL) {
        field = strtok(buf, ",");
        k = 0;
        while(field) {
            data_array[j][k] = atof(field);
            field = strtok(NULL, ",");
            k++;
        }
        j++;
    }

    fclose(fp);
    return;

}

void output_file(int m, char header_list[][m]) {
    for (int i = 0; i < 305; i++) {
        printf("%s\n", header_list[i]);
    }
    return;
}

