#include <stdio.h>
#include <time.h> 
#include <math.h>

#include "m_timer.h"

long get_current_timestamp_ms() {
	long ms;
	time_t s; 

	struct timespec spec; 

	clock_gettime(CLOCK_REALTIME, &spec); 
	return spec.tv_sec * 1000 + (spec.tv_nsec / 1000000);
}