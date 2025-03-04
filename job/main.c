#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include <prom.h>
#include <promhttp.h> // include for HTTP server functionalities

#include "parse.h"
#include "metric.h"

const int NO_OF_COUNTERS = 303;
const int HEADER_LIST_STRING_LENGTH = 70;

static void prom_init(void) {
    // Initialize the default metric collector registry
    prom_collector_registry_default_init();

    // Call metric initialization function
    metric_init();

    // Set the active registry for the HTTP handler
    promhttp_set_active_collector_registry(NULL);
}

int main(int argc, const char **argv) {
    prom_init();
    int status = 0; // status variable to check if metrics have successfully updated

    // parse file cg_16.csv
    char header_list[NO_OF_COUNTERS+2][HEADER_LIST_STRING_LENGTH]; // array of strings called header_list that can have 306 elements and max string length 70
    double data_array[400][NO_OF_COUNTERS+2]; // 2-D array to store all the data

    char *filename = "cg_16.csv";
    int m = HEADER_LIST_STRING_LENGTH;
    int n = NO_OF_COUNTERS+2;

    parse_file(filename, m, header_list, n, data_array);
    output_file(m, header_list); // to print the contents of header_list

    // printf("%f/%f", data_array[202][0], data_array[202][1]);
    // printf("%f/%f", data_array[203][0], data_array[203][1]);
    // printf("%f/%f", data_array[205][0], data_array[205][1]);

    // use do_increment to initialize and store the metrics
    clock_t start, end;
    double time_taken_total = 0;
    for (int i = 0; i < 400; i++) { // change 400 to a variable that tracks number of lines in file during parsing
        // converting error rate and injection rate to a string
        char rate_pair[256];
        snprintf(rate_pair, sizeof(rate_pair), "%.2f/%.2f", data_array[i][0], data_array[i][1]);

        for (int j = 2; j < n; j++) {
            start = clock();
            do_increment_counters(rate_pair, header_list[j], data_array[i][j]);
            end = clock();
            time_taken_total += ((double) (end - start) / CLOCKS_PER_SEC);
        }
    }

    // print time taken for do_increment
    double time_taken_avg = time_taken_total / (NO_OF_COUNTERS * 400);
    printf("time taken for do_increment_counters call: %f\n", time_taken_avg);

    // Start the HTTP server
    struct MHD_Daemon* promtest_daemon = promhttp_start_daemon(MHD_USE_DEBUG|MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL);

    sleep(100);

    printf("\nshutting down...\n");


    prom_collector_registry_destroy(PROM_COLLECTOR_REGISTRY_DEFAULT);
    PROM_COLLECTOR_REGISTRY_DEFAULT = NULL;
  
    // Stop the HTTP server
    MHD_stop_daemon(promtest_daemon);

    return 0;
}
