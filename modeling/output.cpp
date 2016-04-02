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
	logFile << trace << std::endl;
}

void Output::enterFunctionTrace(std::string fileName, std::string trace) {
	printTrace(fileName + ": Entering function", trace);
}

void Output::printTrace(std::string fileName, std::string trace) {
#ifdef TRACEINFILE
	//std::cout << fileName << ": " << trace << std::endl;
#else
#endif
}

void Output::printErrorTrace(std::string fileName, std::string trace) {
	std::cout << "Error trace:" << fileName << ".cpp: " << trace << std::endl;
	system("pause");
}