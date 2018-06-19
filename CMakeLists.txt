cmake_minimum_required(VERSION 2.6)
	# code checks
		add_definitions(-std=c++11)
		add_definitions(-Wall -Wextra)
		add_definitions(-Wconversion)
		add_definitions(-Wshadow)
		add_definitions(-Wstrict-aliasing=2)
		#add_definitions(-pedantic)
		#add_definitions(-ansi)
		add_definitions(-Wno-long-long) # don't warn if long long types are used
		add_definitions(-Wunused-macros)
		# check for multiple definitions (multiple definitions in different compilation units)


# libraries
	add_library(tracer tracer.cpp)
