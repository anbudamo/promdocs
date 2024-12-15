#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <prom.h>
#include <promhttp.h> // include for HTTP server functionalities

#include "parse.h"

// To get started using one of the metric types, declare the metric at file scope
prom_counter_t *my_counter;

int metric_init(void);
int do_increment_counters(const char* label);

// You can create the metric and register it with the default metric collector registry in one chain of functions.
// A metric collector is responsible for collecting metrics and returning them. 
// A metric collector registry is declared in global scope and contains metric collectors
int metric_init(void) {
    my_counter = prom_collector_registry_must_register_metric(prom_counter_new("performance_counter_total", "Performance counter values categorized by event", 1, (const char*[]) { "events" }));
    if (!my_counter) return 1;  // Check if initialization was successful
    return 1;
}

// Now that we have a metric configured for creation and registration, 
// we can update our metric within any of the functions of the file in which it was declared
int do_increment_counters(const char* label) {
    int s = 0;
    printf("Incrementing...");

    printf("Label: %s\n", label);
    printf("my_counter: %p\n", (void*)my_counter);

    s = prom_counter_inc(my_counter, (const char*[]) { label });
    return s;
}

const int NO_OF_COUNTERS = 303;
const int HEADER_LIST_STRING_LENGTH = 70;


int main(int argc, const char **argv) {
    int status = 0; // status variabel to check if metrics have successfully updated

    // Initialize the default metric collector registry
    prom_collector_registry_default_init();
    // Call metric initialization function
    metric_init();
    // Set the active registry for the HTTP handler
    promhttp_set_active_collector_registry(NULL);

    // initialize const char **labels to pass to do function
    const char *labels[] = { "branch-instructions", "cache-misses" };

    // update metric 10 times by calling function do_increment_counters in each label
    char header_list[NO_OF_COUNTERS+2][HEADER_LIST_STRING_LENGTH]; // array of strings called header_list that can have 306 elements and max string length 70
    double data_array[400][NO_OF_COUNTERS+2]; // 2-D array to store all the data

    char *filename = "cg_16.csv";
    int m = HEADER_LIST_STRING_LENGTH;
    int n = NO_OF_COUNTERS+2;

    parse_file(filename, m, header_list, n, data_array);
    output_file(m, header_list);

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


