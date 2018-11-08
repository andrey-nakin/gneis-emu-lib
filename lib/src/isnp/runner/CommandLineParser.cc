#include <memory.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "isnp/runner/CommandLineParser.hh"

isnp::runner::CommandLineParser::CommandLineParser(int argc_, char* argv_[],
		bool const silent) :
		returnCode(0), parsedArgc(0), parsedArgv(nullptr), numOfThreads(0), visualMode(
				false) {
	Parse(argc_, argv_, silent);
}

isnp::runner::CommandLineParser::CommandLineParser(
		CommandLineParser const & src) :
		returnCode(src.returnCode), parsedArgc(src.parsedArgc), parsedArgv(
				Dup(src.parsedArgc, src.parsedArgv)), numOfThreads(
				src.numOfThreads), visualMode(src.visualMode) {

}

isnp::runner::CommandLineParser::~CommandLineParser() {
	delete parsedArgv;
}

void isnp::runner::CommandLineParser::Parse(int argc, char* argv[],
		bool const silent) {

	int res;
	char const * const options = "h?v"
#ifdef G4MULTITHREADED
			"t:"
#endif
;	if (silent) {
		::opterr = 0;
	}

	::optind = 1;	//	reset getopt
	while ((res = ::getopt(argc, argv, options)) != -1) {
		switch (res) {
		case 'v':
			visualMode = true;
			break;
#ifdef G4MULTITHREADED
			case 't':
			numOfThreads = atoi(optarg);
			break;
#endif
		case 'h':
		case '?':
			if (!silent) {
				std::cerr << "Usage: <script file>\n"
						"";
			}
			returnCode = 1;
			break;
		}
	}

	parsedArgc = argc - optind + 1;
	parsedArgv = new char*[parsedArgc];
	parsedArgv[0] = argv[0];
	for (int i = 1; i < parsedArgc; i++) {
		parsedArgv[i] = argv[i + optind - 1];
	}
}

char** isnp::runner::CommandLineParser::Dup(int const argc, char** const argv) {
	char** const result = new char*[argc];
	::memcpy(result, argv, argc * sizeof(result[0]));
	return result;
}
