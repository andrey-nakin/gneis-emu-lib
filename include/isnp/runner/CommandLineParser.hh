#ifndef isnp_runner_CommandLineParser_hh
#define isnp_runner_CommandLineParser_hh

#include <G4String.hh>

namespace isnp {

namespace runner {

/**
 * Class parses command line and retrieves commonly used parameters
 */
class CommandLineParser final {
public:

	CommandLineParser(int argc, char* argv[], bool silent = false);
	CommandLineParser(const CommandLineParser&);
	~CommandLineParser();

	CommandLineParser& operator=(const CommandLineParser&) = delete;

	int GetReturnCode() const {
		return returnCode;
	}

	long GetRandomSeed() const {
		return randomSeed;
	}

	G4String GetFileSuffix() const {
		return fileSuffix;
	}

	int GetArgc() const {
		return parsedArgc;
	}

	char** GetArgv() const {
		return parsedArgv;
	}

private:

	int returnCode;
	long randomSeed;
	G4String fileSuffix;
	int parsedArgc;
	char** parsedArgv;

	void Parse(int argc, char* argv[], bool silent);
	char** Dup(int argc, char** argv);

};

}

}

#endif	//	isnp_runner_CommandLineParser_hh
