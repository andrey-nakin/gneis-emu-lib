#ifndef gneis_runner_BasicRunner_hh
#define gneis_runner_BasicRunner_hh

#include <functional>
#include <G4RunManager.hh>

#include "gneis/runner/CommandLineParser.hh"

namespace gneis {

namespace runner {

/**
 * Class initializes and runs Geant4
 */
class BasicRunner {
public:

	BasicRunner(int argc, char* argv[]);
	virtual ~BasicRunner();

	BasicRunner(BasicRunner const&) = delete;
	BasicRunner& operator=(BasicRunner const&) = delete;

	int Run(std::function<void(G4RunManager&)> closure);

private:

	CommandLineParser const parser;

	static long SystemTime();

};

}

}

#endif	//	gneis_runner_BasicRunner_hh
