#ifndef CMN_DEFINES_H
#define CMN_DEFINES_H

#define NUMBEROFDIMENSIONS 2

#define NUMBEROFCELLSX 30
#define NUMBEROFCELLSY 30

#define WORKTIME 200

#define MAXNUMBEROFNEURONS 5

//(nothing / neuron / axon / dendrite) (0/1/2/3)
#define NOTHING    0
#define NEURON     1
#define AXON       2
#define	DENDRITE   3
#define GROWTHCONE 4

#define NEURONCOLOR GREEN
#define AXONCOLOR   WHITE

#define dynamicArrayRealloc(type, arrayName, numberOfElements)      \
	type *tmpArrayName;                                             \
	tmpArrayName = new type[numberOfElements];                      \
                                                                    \
	if (numberOfElements != 0) {                                    \
		for(int i = 0; i < numberOfElements; i++) {                 \
			tmpArrayName[i] = arrayName[i];                         \
		}                                                           \
        delete [] arrayName;                                        \
	}                                                               \
                                                                    \
	arrayName = new type[++numberOfElements];                       \
                                                                    \
	if (numberOfElements != 0) {                                    \
		for(int i = 0; i < numberOfElements - 1; i++) {             \
			arrayName[i] = tmpArrayName[i];                         \
		}                                                           \
	}                                                               \
                                                                    \
	delete [] tmpArrayName

#include <stdio.h>
#include <cstring> // For strlen

#define logFileName "log.txt"
//TODO:create trace groups
//TODO:it`s better to delete log file before program start in program somehow
#define CELLSTACKTRACES
#define GROWTHCONETRACES
//#define CONNECTIONTRACES
#define TRACE(file, format, ...)            \
		fopen_s(&log, logFileName, "a");    \
		fprintf(log, file);                 \
		fprintf(log, ".cpp: ");             \
		fprintf(log, format, __VA_ARGS__);  \
		fprintf(log, "\n");                 \
		fclose(log);

#define ENTER_FUNCTION(file, function, format, ...)      \
		FILE *log;                                       \
	    TRACE(file, "Entering function %s", function);   \
		if(strlen(format) != 0) { \
			TRACE(file, format, __VA_ARGS__); \
		}
#endif