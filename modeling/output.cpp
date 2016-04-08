#include "output.h"

Output* Output::p_Output = 0;

Output* Output::getOutput() {
	if(!p_Output) {
		p_Output = new Output();
	}
	return p_Output;
}

Output::Output() {
	openOutputFiles();
}

Output::~Output() {
	closeOutputFiles();
}

void Output::openOutputFiles() {
	logFile.open(LOGFILENAME, std::ios::out);
	lenghtStatisticsFile.open(LENGTHSTATISTICSFILE, std::ios::out);
	connectivityGraphStatisticsFile.open(CONNECTIVITYGRAPHSTATISTICSFILE, std::ios::out);
	environmentStatisticsFile.open(ENVIRONMENTSTATISTICSFILE, std::ios::out);
}

void Output::closeOutputFiles(){
	logFile.close();
	lenghtStatisticsFile.close();
	connectivityGraphStatisticsFile.close();
	environmentStatisticsFile.close();
}

void Output::printToFile(int outputFile, std::string trace) {
	switch(outputFile) {
	case LOGFILEID:
		logFile << trace << std::endl;
		break;
#ifdef STATISTICSON
	case LENGTHSTATISTICKSFILEID:
		lenghtStatisticsFile << trace << std::endl;
		break;
	case CONNECTIVITYGRAPHSTATICSFILEID:
		connectivityGraphStatisticsFile << trace << std::endl;
		break;
	case ENVIRONMENTSTATISTICSFILEID:
		environmentStatisticsFile << trace << std::endl;
		break;
#endif
	}
}

void Output::enterFunctionTrace(std::string fileName, std::string trace) {
	printTrace(fileName + ": Entering function", trace);
}

#include <ctime>
void Output::printTrace(std::string fileName, std::string trace) {
	time_t currentTime;
	struct tm localTime;
	currentTime = time(NULL);
	localtime_s(&localTime, &currentTime);

	int Hour   = localTime.tm_hour;
	int Min    = localTime.tm_min;
	int Sec    = localTime.tm_sec;

	trace = std::to_string(Hour) + ":" + std::to_string(Min) + ":" + std::to_string(Sec) + ":" + trace;
#ifdef TRACESON
	#ifdef TRACEINFILE
		printToFile(LOGFILEID, fileName + ": " + trace);
	#else
		std::cout << fileName << ": " << trace << std::endl;
	#endif
#endif
}

void Output::printErrorTrace(std::string fileName, std::string trace) {
	std::cout << "Error trace:" << fileName << ".cpp: " << trace << std::endl;
	system("pause");
}