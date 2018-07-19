#pragma once
#include <time.h>
// time for linux in this
// https://www.binarytides.com/get-time-difference-in-microtime-in-c/
// https://stackoverflow.com/questions/5362577/c-gettimeofday-for-computing-time
// https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html
// https://linux.die.net/man/3/sleep

// really good article with window sinformation as well
// https://www.softwariness.com/articles/monotonic-clocks-windows-and-posix/

// high precision time value
typedef struct timespec Time;

// gets the elapsed time since the beginning
Time UTI_getCurTime();

// gets the difference between 2 times: a - b
Time UTI_timeDiff(const Time a, const Time b);

// returns 0 for the time value
Time UTI_zeroTime();

// casts the time to seconds
float UTI_castTimeToSecs(Time);

// casts seconds to the type Time
Time UTI_castSecsToTime(float);

// time to sleep
void UTI_sleep(Time);
