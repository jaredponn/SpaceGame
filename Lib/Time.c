//#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE

#include "Time.h"
#include <stdio.h>
#include <unistd.h>

// -----------------------------------------
//    Private functoins declarations
// -----------------------------------------

// unsigned int refers to time in microsecoonds
static unsigned int UTI_castTimeToUSecs(Time);

// -----------------------------------------
//    public function implementations
// -----------------------------------------

Time UTI_getCurTime() {
        struct timespec tmp;
        if (clock_gettime(CLOCK_MONOTONIC, &tmp)) {
                return UTI_zeroTime();
        }
        return tmp;
}

Time UTI_timeDiff(const Time a, const Time b) {
        return (Time){.tv_sec = a.tv_sec - b.tv_sec,
                      .tv_nsec = a.tv_nsec - b.tv_nsec};
}

Time UTI_zeroTime() { return (Time){.tv_sec = 0, .tv_nsec = 0}; }

float UTI_castTimeToSecs(Time time) {
        // return ((float)(10 ^ 9) * time.tv_sec) + (float)time.tv_nsec;
        return (float)time.tv_sec + (float)time.tv_nsec / 1000000000;
}

Time UTI_castSecsToTime(float secs) {
        time_t wholesecs = (long int)secs;
        long int fracsecs = (secs - wholesecs) * (1000000000);
        return (Time){.tv_sec = wholesecs, .tv_nsec = fracsecs};
}

void UTI_sleep(Time time) { usleep(UTI_castTimeToUSecs(time)); }
// -----------------------------------------
//    private function implementations
// -----------------------------------------

static unsigned int UTI_castTimeToUSecs(Time val) {
        return (val.tv_sec * 1000000) + (val.tv_nsec / 1000);
}
