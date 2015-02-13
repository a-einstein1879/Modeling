#ifndef CMN_DEFINES_H
#define CMN_DEFINES_H

#define NUMBEROFDIMENSIONS 2

#define NUMBEROFCELLSX 20
#define NUMBEROFCELLSY 20

#define MAXNUMBEROFNEURONS 5

//(nothing / neuron / axon / dendrite) (0/1/2/3)
#define NOTHING    0
#define NEURON     1
#define AXON       2
#define	DENDRITE   3
#define GROWTHCONE 4

#include <stdio.h>

#define TRACE(file, format, ...) \
   printf(file);                 \
   printf(".cpp: ");             \
   printf(format, __VA_ARGS__);

#endif