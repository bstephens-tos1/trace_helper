#include "tracer.h"
#include <iostream>

using namespace std;

/*
 *  Use this to write to trace files which expect a 1 or 0 to
 *  turn off/on the trace feature.  This can also be used to clear
 *  the trace ring buffer, by writing an empty string to <path>/trace
 */
void switch_state(string state, string path)
{
    ofstream of;

    of.open(path);

    if (!of.is_open()) {
        cerr << "Error opening " << path << endl;
        exit(1);
    }

    of << state;
    
    of.close();
}

void
Tracer::init()
{
    // Clears the ring buffer
    switch_state("", "/debug/tracing/trace");

    switch_state("1", "/debug/tracing/events/irq/softirq_entry/enable");
    switch_state("1", "/debug/tracing/events/irq/softirq_exit/enable");

    _trace.open("/debug/tracing/tracing_on");

    if (!_trace.is_open()) {
        cerr << "Error opening /debug/tracing/tracing_on" << endl;
        exit(1);
    }
}

void
Tracer::start()
{
    _trace << "1";
    _trace.close();
}

void
Tracer::start_proc_trace()
{
	switch_state("", "/debug/tracing/trace");
	switch_state("function", "/debug/tracing/current_tracer");
	switch_state("1", "/debug/tracing/tracing_on");
}

void
Tracer::stop_proc_trace()
{
	switch_state("0", "/debug/tracing/tracing_on");
}

void
Tracer::stop()
{
    switch_state("0", "/debug/tracing/tracing_on");
    switch_state("0", "/debug/tracing/events/irq/softirq_entry/enable");
    switch_state("0", "/debug/tracing/events/irq/softirq_exit/enable");
}

string
Tracer::getTraceInfo()
{
    string info = "";

    ifstream trace;
    trace.open("/debug/tracing/trace");

    if (!trace.is_open()) {
        cerr << "Error opening /debug/tracing/trace";
        exit(1);
    }
    string line;
    bool recorded_first_value = false;    
    string prev_val = "";	

    while (!trace.eof()) {
    	prev_val = line;
	getline(trace, line);

	if (line[0] == '#')
		continue;
	if (!recorded_first_value) {
		info = info + line + "\n";
		recorded_first_value = true;
	}
    }
   
   info = info + prev_val + "\n";

    trace.close();
    return info;
}
