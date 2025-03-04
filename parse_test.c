#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("cg_16.csv", "r");
    if (!fp) {
        printf("Can't open file.\b");
        return 1;
    }

    // get the first line from the csv file containing the list of CPU counters using fgets()
    // parse and store that line into a string array
    
    // creating an array of char* to store each string, using malloc to dynamically allocate
    char **counter_list = malloc (400 * sizeof(char *));
    for (int i = 0; i < 2; i++) {
        counter_list[i] = malloc(12 * sizeof(char));
    }
    for (int i = 2; i < 400; i++) {
        counter_list[i] = malloc(70 * sizeof(char));
    }

    int i = 0;
    char buf[10000]; // 8500 character buf | 306 counters
    while(fgets(buf, 10000, fp)) {
        // field points to first string in buf
        char *field = strtok(buf, ",");

        // store er and ir in first two indexes of array counter_list
        counter_list[i] = field;
        i++;
        field = strtok(NULL, ",");
        counter_list[i] = field;
        i++;

        // store the list of counters in array counter_list 
        while(field) {
            // printf("%s\n", field);
            // passing NULL tells strtok to continue tokenizing string from where it left off
            field = strtok(NULL, ",");
            counter_list[i] = field;
            i++;
        }
    }

    for (int i = 0; i < 306; i++) {
        printf("%s\n", counter_list[i]);
    }

    // int i = 1;
    // fgets(buf, 8500, fp);
    // // field points to first string in buf
    // char *field = strtok(buf, ",");
    // while(field) {
    //     i++;
    //     printf("%s\n", field);
    //     // passing NULL tells strtok to continue tokenizing string from where it left off
    //     field = strtok(NULL, ",");
    // }
    // printf("%d", i);
    
    
    fclose(fp);
    for (int i = 0; i < 200; i++) {
        free(counter_list[i]);
    }
    free(counter_list);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int NO_OF_COUNTERS = 303;
const int HEADER_LIST_STRING_LENGTH = 70;

int main() {
    FILE *fp = fopen("cg_16.csv", "r");
    if (!fp) {
        printf("Can't open file.\b");
        return 1;
    }

    /* get the first line from the csv file containing the list of CPU counters using fgets() */ 
    /* parse and store that line into a string array */ 

    char buf[10000]; // 8500 character buf | 306 counters
    char header_list[NO_OF_COUNTERS+2][HEADER_LIST_STRING_LENGTH]; // array of strings called header_list that can have 306 elements and max string length 70
    int i = 0; // header_list index value

    // get first line of the csv file, parse using strtok and store contents in header_list
    fgets(buf, 10000, fp);
    char *field = strtok(buf, ",");
    while(field) {
        strcpy(header_list[i], field);
        field = strtok(NULL, ",");
        i++;
    }

    // output header_list
    for (int i = 0; i < 305; i++) {
        printf("%s\n", header_list[i]);
    }

    /* parse the remaining lines from the file and store the csv data in an n * m matrix */ 

    double data_array[400][NO_OF_COUNTERS+2]; // 2-D array to store all the data
    int j, k = 0; // index variables for the 2-D array 

    // get each line, parse using strtok 
    while(fgets(buf, 10000, fp) != NULL) {
        field = strtok(buf, ",");
        k = 0;
        while(field) {
            if (k > 304) {
                printf("exceeded column limit - k\n");
                printf("last value: %f\n", data_array[j][k - 1]);
                return 1;
            }
            data_array[j][k] = atof(field);
            field = strtok(NULL, ",");
            k++;
        }
        j++;
    }

    
    
    
    
    fclose(fp);
    return 0;
}
