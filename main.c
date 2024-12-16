#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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

    // use do_increment to initialize and store metrics
    const char *labels[] = { "branch-instructions", "cache-misses" }; // initialize const char **labels to pass to do function
    for (int i = 0; i < 400; i++) { // change 400 to a variable that tracks number of lines in file during parsing
        // converting error rate and injection rate to a string
        char rate_pair[256];
        snprintf(rate_pair, sizeof(rate_pair), "%f/%f", round(data_array[i][0] * 100 / 100), round(data_array[i][1] * 100 / 100));

        for (int j = 2; j < n; j++) {
            do_increment_counters(rate_pair, header_list[j], data_array[i][j]);
        }
    }

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


