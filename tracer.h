#ifndef TRACER_H
#define TRACER_H

#include <string>
#include <fstream>

class Tracer
{
public:
    void init();

    void start();
    void stop();

    void start_proc_trace();
    void stop_proc_trace();
    std::string getTraceInfo();
private:
    std::ofstream _trace;
};

#endif
