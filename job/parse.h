#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_file(char *filename, int m, char header_list[][m], int n, double data_array[][n]);
void output_file(int m, char header_list[][m]);

#endif // PARSE_H
