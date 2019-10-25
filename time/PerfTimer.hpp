#include <iostream>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> Timestamp;

class PerfTimer
{
public:
    PerfTimer(const char* timerName)
    {
        m_name = std::string(timerName);
        
        // Start the timer
        m_startTime = Clock::now();
    }
    
    ~PerfTimer()
    {
        Timestamp endTime = Clock::now();
        std::chrono::nanoseconds elapsed = (endTime - m_startTime);
        
        // Output timer duration in milliseconds
        std::cout << m_name.c_str() << ": " << (double)elapsed.count() / 1000000 << " milliseconds" << std::endl;
    }
    
private:
    Timestamp m_startTime;
    std::string m_name;
};

#ifndef SHIPPING_BUILD

#define CreateFcnTimer PerfTimer __func__timer(__func__)

// The 'x' in 'xtimer' is replaced by whatever string is passed into the scope timer
// but the quotations are removed. So if the calling code is ScopeTimer("stuff")
// then 'xtimer' becomes 'timerstuff'. This makes sure every timer name is unique
// within the scoe it is used.
#define ScopeTimer(x) PerfTimer xtimer(x)

#else
// The timers can be shut off in shipping builds by replacing their standard
// macros with these.
#define CreateFcnTimer ((void)0)
#define ScopeTimer(x) ((void)0)

#endif