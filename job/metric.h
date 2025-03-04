#ifndef METRIC_H
#define METRIC_H

int metric_init(void);
int do_increment_counters(const char* rate_pair, const char* counter_name, double counter_value);


#endif // METRIC_H
