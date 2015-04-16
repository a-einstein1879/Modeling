#ifndef SETTINGS_H
#define SETTINGS_H

#define NUMBEROFDIMENSIONS 2

#define NUMBEROFCELLSX 20
#define NUMBEROFCELLSY 20

#define WORKTIME 5

#define MAXNUMBEROFNEURONS 2
#define MAXNUMBEROFGROWTHCONES 16

#define INTERACTION00 ( double(0 ) )
#define INTERACTION01 ( double(0 ) )
#define INTERACTION11 ( double(0 ) )
#define INTERACTION10 ( double(1) )
#define NUMBEROFNEURONTYPES 2
/*#define INTERACTION(type1, type2) ( double(INTERACTION##type1##type2) )*/
//#define DIFFUSIONVISIBLE

#define CLUI
//#define GUI

#define TRACEINFILE
//#define CELLSTACKTRACES
//#define GROWTHCONETRACES
//#define CONNECTIONTRACES
//#define BRANCHINGTRACES

#define LOGFILENAME     "log.txt"
#define STATISTICSFILE  "log-statistics.txt"

#define AXONGROWTH
//#define DENDRITEGROWTH
#endif