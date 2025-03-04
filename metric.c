#include <prom.h>
#include <stdio.h>

#include "metric.h"

// To get started using one of the metric types, declare the metric at file scope
prom_counter_t *my_counter;

// You can create the metric and register it with the default metric collector registry in one chain of functions.
// A metric collector is responsible for collecting metrics and returning them. 
// A metric collector registry is declared in global scope and contains metric collectors
int metric_init(void) {
    my_counter = prom_collector_registry_must_register_metric(
        prom_counter_new(
            "performance_counter_total", 
            "Performance counter values categorized by event", 
            2, 
            (const char*[]) { "rate_pair", "event" }));
    if (!my_counter) return 1;  // Check if initialization was successful
    return 0;
}

// Now that we have a metric configured for creation and registration, 
// we can update our metric within any of the functions of the file in which it was declared
int do_increment_counters(const char* rate_pair, const char* counter_name, double counter_value) {
    int s = 0;
    printf("Incrementing...");
    printf("my_counter: %p\n", (void*)my_counter);
    printf("Label: %s %s\n", rate_pair, counter_name);

    s = prom_counter_add(my_counter, counter_value, (const char*[]) { rate_pair, counter_name });
    return s;
}
